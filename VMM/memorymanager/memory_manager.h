#ifndef MEMORY_MANAGER_H_
#define MEMORY_MANAGER_H_

#include <memory> //not to be confused with namespace memory

#include "..\utils\types.h"
#include "..\utils\parameters.h"
#include "memory\main_memory.h"
#include "memory\page_table.h"
#include "memory\tlb.h"

namespace vmm {
using MainMemoryPtr = std::unique_ptr<memory::MainMemory>;
using PageTablePtr = std::unique_ptr<memory::PageTable>;
using TLBPtr = std::unique_ptr<memory::TLB>;

class MemoryManager {
public:
	MemoryManager() = default;
	~MemoryManager() = default;

	bool SetupFailed();
	Byte ReadAddress(AddressType);

private:

	MainMemoryPtr main_memory_;
	PageTablePtr page_table_;
	TLBPtr tlb_;

};


} //end of namespace vmm



#endif

