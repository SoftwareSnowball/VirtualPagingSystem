#ifndef TEST_PAGE_TABLE_H_
#define TEST_PAGE_TABLE_H_


#include "..\memorymanager\memory\page_table.h"

#include "..\external\catch.hpp"

using namespace vmm::memory;
using namespace vmm_parameters;

TEST_CASE("Test page table", "[PageTable]") {
	
	SimulationParameters parameters;
	PageTable page_table(parameters.number_of_frames_);

	FrameNumber frame;

	page_table.GetEmpty(&frame);


	REQUIRE(frame == 0);

}
#endif