#include <memory>

#include "memory_manager.h"

namespace vmm {

MemoryManager::MemoryManager(ParametersManagedPtr parameters)
	:parameters_(std::move(parameters)) {
	main_memory_ = MainMemoryManagedPtr(new memory::MainMemory(parameters_->frame_size_, parameters_->number_of_frames_));
	page_table_ = PageTableManagedPtr(new memory::PageTable(parameters_->number_of_frames_));
	tlb_ = TLBManagedPtr(new memory::TLB(parameters_->num_tlb_entries_));
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

MemoryManagerResult MemoryManager::getError(std::string* error) {
	return MemoryManagerResult::kNotImplemented;
}

Byte MemoryManager::ReadAddress(LogicalAddress) {
	return 0xFF;
}

MemoryManagerResult MemoryManager::getPage(LogicalAddress address, PageNumber* page) {
	if (address > (2 << (parameters_->page_size_bits + parameters_->page_table_size_bits))) {
		return MemoryManagerResult::kAddressInvalid;
	}

	*page = address >> parameters_->page_size_bits;
	return MemoryManagerResult::kSuccess;
}

MemoryManagerResult MemoryManager::getOffset(LogicalAddress address, AddressOffset* offset) {
	if (address > (2 << (parameters_->page_size_bits + parameters_->page_table_size_bits))) {
		return MemoryManagerResult::kAddressInvalid;
	}

	return MemoryManagerResult::kSuccess;
}


} //end of namespace vmm