#ifndef MEMORY_MANAGER_H_
#define MEMORY_MANAGER_H_

#include <memory> //not to be confused with namespace memory
#include <string>

#include "..\utils\types.h"
#include "..\utils\parameters.h"
#include "memory\main_memory.h"
#include "memory\page_table.h"
#include "memory\tlb.h"

namespace vmm {
	using ParametersManagedPtr = std::unique_ptr<vmm_parameters::SimulationParameters>;
	
	namespace memory {
		using MainMemoryManagedPtr = std::unique_ptr<memory::MainMemory>;
		using PageTableManagedPtr = std::unique_ptr<memory::PageTable>;
		using TLBManagedPtr = std::unique_ptr<memory::TLB>;
	} //end of namespace memory
	
	class MemoryManager {
	public:
		MemoryManager(ParametersManagedPtr parameters);
		~MemoryManager();
	
		bool SetupFailed();
		std::string getError();
		Byte ReadAddress(AddressType);
	
	private:
		memory::MainMemoryManagedPtr main_memory_;
		memory::PageTableManagedPtr page_table_;
		memory::TLBManagedPtr tlb_;
	
};
} //end of namespace vmm


#endif

