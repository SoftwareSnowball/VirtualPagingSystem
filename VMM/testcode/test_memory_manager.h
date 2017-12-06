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



#include "..\external\catch.hpp"
#include "..\utils\parameters.h"
#include "..\memorymanager\memory_manager.h"

TEST_CASE("Test Memory Manager Init", "[VMM]") {

	std::unique_ptr<vmm_parameters::SimulationParameters> parameters(new vmm_parameters::SimulationParameters);
	vmm::MemoryManager manager(std::move(parameters));

	REQUIRE(parameters == nullptr); //parameters' ownership should be moved to the manager

	REQUIRE(manager.SetupFailed() == false);
}


#endif