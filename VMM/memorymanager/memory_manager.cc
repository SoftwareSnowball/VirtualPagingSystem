#include <memory>

#include "memory_manager.h"

namespace vmm {

MemoryManager::MemoryManager(ParametersManagedPtr parameters)
{
	main_memory_ = MainMemoryManagedPtr(new memory::MainMemory(parameters->frame_size_, parameters->number_of_frames_));
	page_table_ = PageTableManagedPtr(new memory::PageTable(parameters->number_of_frames_));
	tlb_ = TLBManagedPtr(new memory::TLB(parameters->num_tlb_entries_));
	setup_failed_ = false;
	return;
}

MemoryManager::~MemoryManager()
{
	main_memory_ = nullptr;
	page_table_ = nullptr;
	tlb_ = nullptr;
	return;
}


bool MemoryManager::SetupFailed() {
	return setup_failed_;
}

std::string MemoryManager::getError() {
	return std::string("Feature not implemented");
}

Byte MemoryManager::ReadAddress(LogicalAddress)
{




}


} //end of namespace vmm