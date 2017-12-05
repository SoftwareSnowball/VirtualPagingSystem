#ifndef TEST_BACKINGSTORE_H_
#define TEST_BACKINGSTORE_H_

/*
Module:	BackingstoreManager
Purpose: Reads pages from the backingstore
Methods: 
	Constructor
	Destructor
	GetPage

Constructor
	Takes in the simulation parameters
	creates manager

Destructor
	Kills things

GetPage
	Gets a specific page out of memory and copies data to a given memory address

*/

#include <memory>
#include <iostream>

#include "..\memorymanager\backingstore\backingstore_manager.h"
#include "..\external\catch.hpp"


using namespace vmm::memory; //in order to get the test code done quickly

TEST_CASE("Test the backing store manager", "[Backingstore]") {

	std::unique_ptr<vmm_parameters::SimulationParameters> params( new vmm_parameters::SimulationParameters);
	BackingstoreManager manager(params.get());
	Byte* data = new Byte[params->page_size_];
	int return_code;

	SECTION("Testing basic usage of GetPage") {
		return_code = manager.GetPage(0, data);
		REQUIRE(data[0] == 0);
		REQUIRE(data[1] == 0);
		REQUIRE(data[2] == 0);
		REQUIRE(data[3] == 0);
		REQUIRE(data[4] == 0);
		REQUIRE(data[5] == 0);
		REQUIRE(data[7] == 1);
	}

	SECTION("Testing page out of range") {

		return_code = manager.GetPage(6000000, data);
		REQUIRE(return_code == kIndexOutOfBounds);

	}

	delete[] data;
	params = nullptr;
}

TEST_CASE("Testing backingstore manager with bad backingstore path", "[Backingstore]") {

	std::unique_ptr<vmm_parameters::SimulationParameters> params(new vmm_parameters::SimulationParameters);
	BackingstoreManager manager(params.get(), std::string("fail"));
	Byte* data = new Byte[params->page_size_];
	bool exception_thrown = false;

	try {
		int return_code = manager.GetPage(2, data);
	}
	catch (std::exception& e) {
		exception_thrown = true;
	}

	REQUIRE(exception_thrown);

}




#endif

