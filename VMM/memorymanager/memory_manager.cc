#include <memory>

#include "memory_manager.h"

namespace vmm {

MemoryManager::MemoryManager(ParametersManagedPtr parameters)
	:parameters_(std::move(parameters)) {
	backingstore_ = BackingStoreManagedPtr(new memory::BackingstoreManager(parameters_.get()));
	main_memory_ = MainMemoryManagedPtr(new memory::MainMemory(parameters_->frame_size_, parameters_->number_of_frames_));
	page_table_ = PageTableManagedPtr(new memory::PageTable(parameters_->number_of_frames_));
	tlb_ = TLBManagedPtr(new memory::TLB(parameters_->num_tlb_entries_));

	offset_mask_ = 0;
	for (int i = 0; i < parameters_->page_size_bits; i++) {
		offset_mask_ |= 1 << i;
	}

	page_mask_ = 0;
	for (int i = parameters_->page_size_bits; i < parameters_->page_size_bits + parameters_->page_table_size_bits; i++) {
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

MemoryManagerResult MemoryManager::ReadAddress(LogicalAddress address, Byte* data) {
	
	PageNumber page;
	AddressOffset offset;

	if (GetPage(address, &page) != MemoryManagerResult::kSuccess)
		return MemoryManagerResult::kFailed;

	if (GetOffset(address, &offset) != MemoryManagerResult::kSuccess)
		return MemoryManagerResult::kFailed;

	
	FrameNumber frame_number;
	Byte* frame_ptr;

	if (tlb_->GetFrame(page, &frame_number) != memory::TLBResult::kHit) {
		if (page_table_->GetFrame(page, &frame_number) != memory::PageTableResult::kHit) {	

			page_table_->GetEmpty(&frame_number);
			frame_ptr = main_memory_->getFrameAddress(frame_number);
			backingstore_->GetPage(page, frame_ptr);

			page_table_->Update(page, frame_number);

		}
		tlb_->Update(page, frame_number);
	}

	frame_ptr = main_memory_->getFrameAddress(frame_number);

	*data = frame_ptr[offset];

	return MemoryManagerResult::kSuccess;

}

MemoryManagerResult MemoryManager::GetPage(LogicalAddress address, PageNumber* page) {
	if (address > (2 << (parameters_->page_size_bits + parameters_->page_table_size_bits))) {
		error_message_ = "Address size is too large for current settings";
		return MemoryManagerResult::kAddressInvalid;
	}

	*page = address & page_mask_;
	*page = *page >> parameters_->page_size_bits;
	return MemoryManagerResult::kSuccess;
}

MemoryManagerResult MemoryManager::GetOffset(LogicalAddress address, AddressOffset* offset) {
	if (address > (2 << (parameters_->page_size_bits + parameters_->page_table_size_bits))) {
		error_message_ = "Address size is too large for current settings";
		return MemoryManagerResult::kAddressInvalid;
	}

	*offset = address & offset_mask_;
	
	return MemoryManagerResult::kSuccess;
}


} //end of namespace vmm