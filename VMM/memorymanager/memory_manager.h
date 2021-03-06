#ifndef MEMORY_MANAGER_H_
#define MEMORY_MANAGER_H_

#include <memory> //not to be confused with namespace memory
#include <string>

#include "../utils/types.h"
#include "../utils/parameters.h"
#include "memory/main_memory.h"
#include "memory/page_table.h"
#include "memory/tlb.h"
#include "backingstore/backingstore_manager.h"

#define TLB_REPLACE_FIFO '1'
#define TLB_REPLACE_LRU '2'

namespace vmm {
using ParametersManagedPtr = std::unique_ptr<vmm_parameters::SimulationParameters>;
using MainMemoryManagedPtr = std::unique_ptr<memory::MainMemory>;
using PageTableManagedPtr = std::unique_ptr<memory::PageTable>;
using BackingStoreManagedPtr = std::unique_ptr<memory::BackingstoreManager>;
using TLBManagedPtr = std::unique_ptr<memory::TLB>;

enum struct MemoryManagerResult {
	kSuccess,
	kAddressInvalid,
	kNoDataAtAddress,
	kNotImplemented,
	kFailed
};


class MemoryManager {
public:
	MemoryManager(ParametersManagedPtr parameters);
	~MemoryManager();

	bool SetupFailed();
	std::string GetErrorMessage();

	MemoryManagerResult ReadAddress(LogicalAddress, Byte* data, PhyscialAddress* phys_addr = nullptr);
	MemoryManagerResult GetParameterSummary(std::string* summary);
	MemoryManagerResult SetTLBReplacementPolicy(char policy);

	float GetPageFaultRate();
	float GetTLBHitRate();

#ifndef _DEBUG
private:
#endif
	MemoryManagerResult GetPage(LogicalAddress address, PageNumber* page);
	MemoryManagerResult GetOffset(LogicalAddress address, AddressOffset* offset);
	inline MemoryManagerResult GetPhysical(FrameNumber frame, AddressOffset offset, PhyscialAddress* phys);

private:
	BitMask offset_mask_;
	BitMask page_mask_;
	bool setup_failed_;
	std::string error_message_;

	int number_reads_;
	int tlb_misses_;
	int page_faults_;

	BackingStoreManagedPtr backingstore_;
	ParametersManagedPtr parameters_;
	MainMemoryManagedPtr main_memory_;
	PageTableManagedPtr page_table_;
	TLBManagedPtr tlb_;

};
} //end of namespace vmm


#endif

