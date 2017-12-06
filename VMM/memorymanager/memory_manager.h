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
using MainMemoryManagedPtr = std::unique_ptr<memory::MainMemory>;
using PageTableManagedPtr = std::unique_ptr<memory::PageTable>;
using TLBManagedPtr = std::unique_ptr<memory::TLB>;

enum struct MemoryManagerResult {
	kSuccess,
	kAddressInvalid,
	kNoDataAtAddress,
	kNotImplemented
};


class MemoryManager {
public:
	MemoryManager(ParametersManagedPtr parameters);
	~MemoryManager();

	bool SetupFailed();
	MemoryManagerResult getError(std::string* error);

	Byte ReadAddress(LogicalAddress);

#ifndef _DEBUG
private:
#endif
	MemoryManagerResult getPage(LogicalAddress address, PageNumber* page);
	MemoryManagerResult getOffset(LogicalAddress address, AddressOffset* offset);

private:
	bool setup_failed_;

	ParametersManagedPtr parameters_;
	MainMemoryManagedPtr main_memory_;
	PageTableManagedPtr page_table_;
	TLBManagedPtr tlb_;

};
} //end of namespace vmm


#endif

