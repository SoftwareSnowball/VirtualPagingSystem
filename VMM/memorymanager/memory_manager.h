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
using SimulationParametersManagedPtr = std::unique_ptr<vmm_parameters::SimulationParameters>;
using MainMemoryManagedPtr = std::unique_ptr<memory::MainMemory>;
using PageTableManagedPtr = std::unique_ptr<memory::PageTable>;
using TLBManagedPtr = std::unique_ptr<memory::TLB>;

class MemoryManager {
public:
	MemoryManager(SimulationParametersManagedPtr parameters);
	~MemoryManager();

	bool SetupFailed();
	std::string GetErrorMsg();
	Byte ReadAddress(LogicalAddress);

private:
	PageNumber ParsePageNumber(LogicalAddress logical_address);
	LogicalAddress ParseOffset(LogicalAddress logical_address);


private:
	MainMemoryManagedPtr main_memory_;
	PageTableManagedPtr page_table_;
	TLBManagedPtr tlb_;

};


} //end of namespace vmm



#endif

