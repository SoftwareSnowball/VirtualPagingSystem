#ifndef TEST_MEMORY_MANAGER_H_
#define TEST_MEMORY_MANAGER_H_


/*
Module:	MemoryManager
Purpose: 
	High level module. Takes a logical address and returns the data at that address.
	It also initializes all the other data structures needed for the VMM

Methods:
	Constructor
	Decondstructor
	SetupFailed
	ReadAddress


Method: Constructor
Purpose:
	Creates MemoryManager object.
	Checks information in parameter globals for validity
	Initializes MainMemory, PageTable, and TLB.
	sets the init_failed flag if applicable

inputs:
	parameters struct

*/



#include "../external/catch.hpp"
#include "../utils/parameters.h"
#include "../memorymanager/memory_manager.h"

TEST_CASE("Test Memory Manager Init", "[VMM]") {

	std::unique_ptr<vmm_parameters::SimulationParameters> parameters(new vmm_parameters::SimulationParameters);
	vmm::MemoryManager manager(std::move(parameters));


	SECTION("Test get byte") {
		Byte data;
		//test addresses and values were picked using a seperate binary viewer application
		manager.ReadAddress(0xA4D3, &data);
		REQUIRE(data == 0x34);

		manager.ReadAddress(0x0083, &data);
		REQUIRE(data == 0x20);

		manager.ReadAddress(0xF2AB, &data);
		REQUIRE(data == 0xAA);

		manager.ReadAddress(0x81D6, &data);
		REQUIRE(data == 0x20);

		manager.ReadAddress(0x483F, &data);
		REQUIRE(data == 0x0F);

	}


	SECTION("Test private functions") {
		PageNumber page;
		LogicalAddress address;
		AddressOffset offset;
		vmm::MemoryManagerResult result;

		REQUIRE(parameters == nullptr); //parameters' ownership should be moved to the manager
		REQUIRE(manager.SetupFailed() == false);

		address = 0xAFD4;
		result = manager.GetPage(address, &page);
		REQUIRE(page == 0xAF);
		REQUIRE(result == vmm::MemoryManagerResult::kSuccess);

		address = 0xFFFF;
		result = manager.GetPage(address, &page);
		REQUIRE(page == 255);
		REQUIRE(result == vmm::MemoryManagerResult::kSuccess);

		address = 0xFFFFF;
		result = manager.GetPage(address, &page);
		REQUIRE(result == vmm::MemoryManagerResult::kAddressInvalid);

		address = 0xFFFF;
		result = manager.GetOffset(address, &offset);
		REQUIRE(offset == 255);
		REQUIRE(result == vmm::MemoryManagerResult::kSuccess);

		address = 0xA1B3;
		result = manager.GetOffset(address, &offset);
		REQUIRE(offset == 0xB3);
		REQUIRE(result == vmm::MemoryManagerResult::kSuccess);

		address = 0xAA1B3;
		result = manager.GetOffset(address, &offset);
		REQUIRE(result == vmm::MemoryManagerResult::kAddressInvalid);

		address = 0xF2A3;
		result = manager.GetOffset(address, &offset);
		REQUIRE(offset == 163);



	}

	
}


#endif