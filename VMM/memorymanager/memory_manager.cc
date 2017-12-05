#include "memory_manager.h"


namespace vmm {

	MemoryManager::MemoryManager(ParametersManagedPtr parameters)
	{
		main_memory_ = MainMemoryManagedPtr(new memory::MainMemory);
		page_table_ = PageTableManagedPtr(new memory::PageTable);
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