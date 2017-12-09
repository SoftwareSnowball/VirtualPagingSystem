#include <memory>

#include "memory_manager.h"

namespace vmm {

MemoryManager::MemoryManager(ParametersManagedPtr parameters)
	:parameters_(std::move(parameters)) {
	backingstore_ = BackingStoreManagedPtr(new memory::BackingstoreManager(parameters_.get()));
	main_memory_ = MainMemoryManagedPtr(new memory::MainMemory(parameters_->frame_size_, parameters_->number_of_frames_));
	page_table_ = PageTableManagedPtr(new memory::PageTable(parameters_->number_of_frames_));
	tlb_ = TLBManagedPtr(new memory::TLB(parameters_->num_tlb_entries_));

	number_reads_ = 0;
	page_faults_ = 0;
	tlb_misses_ = 0;

	if (parameters_->backingstore_size_ == 0) {
		parameters_->backingstore_size_ = backingstore_->GetBackingStoreSize();
	}

	offset_mask_ = 0;
	for (int i = 0; i < parameters_->page_size_bits_; i++) {
		offset_mask_ |= 1 << i;
	}

	page_mask_ = 0;
	for (int i = parameters_->page_size_bits_; i < parameters_->page_size_bits_ + parameters_->page_table_size_bits_; i++) {
		page_mask_ |= 1 << i;
	}

	error_message_ = "no error";
	setup_failed_ = false;
	return;
}

MemoryManager::~MemoryManager() {
	main_memory_ = nullptr;
	page_table_ = nullptr;
	tlb_ = nullptr;
	return;
}


bool MemoryManager::SetupFailed() {
	return setup_failed_;
}

std::string MemoryManager::GetErrorMessage() {
	return error_message_;
}

MemoryManagerResult MemoryManager::ReadAddress(LogicalAddress address, Byte* data, PhyscialAddress* phys_addr) {
	
	PageNumber page;
	AddressOffset offset;

	if (GetPage(address, &page) != MemoryManagerResult::kSuccess)
		return MemoryManagerResult::kFailed;

	if (GetOffset(address, &offset) != MemoryManagerResult::kSuccess)
		return MemoryManagerResult::kFailed;

	
	FrameNumber frame_number;
	Byte* frame_ptr;

	if (tlb_->GetFrame(page, &frame_number) != memory::TLBResult::kHit) {
		tlb_misses_++;
		if (page_table_->GetFrame(page, &frame_number) != memory::PageTableResult::kHit) {	
			page_faults_++;
			page_table_->GetEmpty(&frame_number);
			frame_ptr = main_memory_->GetFrameAddress(frame_number);
			backingstore_->GetPage(page, frame_ptr);

			page_table_->Update(page, frame_number);

		}
		tlb_->Update(page, frame_number);
	}

	frame_ptr = main_memory_->GetFrameAddress(frame_number);

	number_reads_++;
	GetPhysical(frame_number, offset, phys_addr);
	*data = frame_ptr[offset];

	return MemoryManagerResult::kSuccess;

}

MemoryManagerResult MemoryManager::GetParameterSummary(std::string* summary) {

	if (summary == nullptr) {
		return MemoryManagerResult::kFailed;
		error_message_ = "string pointer is null";
	}

	summary->resize(400);

	Count logical_pages = parameters_->backingstore_size_ / parameters_->page_size_;

	*summary = "Number of logical pages: " + std::to_string(logical_pages) + "\n";
	*summary += "Page size: " + std::to_string(parameters_->page_size_) + "\n";
	*summary += "Page table size: " + std::to_string(parameters_->page_table_size_) + "\n";
	*summary += "TLB size: " + std::to_string(parameters_->num_tlb_entries_) + "\n";
	*summary += "Number of physical frames: " + std::to_string(parameters_->number_of_frames_) + "\n";
	*summary += "Physical Memory size: " + std::to_string(parameters_->number_of_frames_ * parameters_->frame_size_) + "\n";

	return MemoryManagerResult::kSuccess;
}

MemoryManagerResult MemoryManager::SetTLBReplacementPolicy(char policy)
{
	if (policy == TLB_REPLACE_FIFO) {
		tlb_->DisableLRU();
		return MemoryManagerResult::kSuccess;
	}
	else if (policy == TLB_REPLACE_LRU) {
		tlb_->EnableLRU();
		return MemoryManagerResult::kSuccess;
	}

	return MemoryManagerResult::kFailed;
}

float MemoryManager::GetPageFaultRate()
{
	return float(page_faults_) / float(number_reads_);
}

float MemoryManager::GetTLBHitRate()
{
	return float(number_reads_ - tlb_misses_) / float(number_reads_);
}

MemoryManagerResult MemoryManager::GetPage(LogicalAddress address, PageNumber* page) {
	if (address > (2 << (parameters_->page_size_bits_ + parameters_->page_table_size_bits_))) {
		error_message_ = "Address size is too large for current settings";
		return MemoryManagerResult::kAddressInvalid;
	}

	*page = address & page_mask_;
	*page = *page >> parameters_->page_size_bits_;
	return MemoryManagerResult::kSuccess;
}

MemoryManagerResult MemoryManager::GetOffset(LogicalAddress address, AddressOffset* offset) {
	if (address > (2 << (parameters_->page_size_bits_ + parameters_->page_table_size_bits_))) {
		error_message_ = "Address size is too large for current settings";
		return MemoryManagerResult::kAddressInvalid;
	}

	*offset = address & offset_mask_;
	
	return MemoryManagerResult::kSuccess;
}

inline MemoryManagerResult MemoryManager::GetPhysical(FrameNumber frame, AddressOffset offset, PhyscialAddress* phys) {
	if (phys == nullptr) {
		return MemoryManagerResult::kFailed;
	}

	*phys = offset | (frame << parameters_->page_size_bits_);

	return MemoryManagerResult::kSuccess;
}


} //end of namespace vmm