#include <memory>

#include "memory_manager.h"

namespace vmm {

	MemoryManager::MemoryManager(ParametersManagedPtr parameters)
	{
	//	main_memory_ = MainMemoryManagedPtr(new memory::MainMemory(parameters->frame_size_, parameters->number_of_frames_));
	//	page_table_ = PageTableManagedPtr(new memory::PageTable(parameters->number_of_frames_));
		tlb_ = TLBManagedPtr(new memory::TLB);
	
		return;
	}
	
	MemoryManager::~MemoryManager()
	{
		return;
	}
	
	
	bool MemoryManager::SetupFailed() {
		return false;
	}
	
	std::string MemoryManager::getError() {
	
		return std::string("Feature not implemented");
	
	}
	

} //end of namespace vmm