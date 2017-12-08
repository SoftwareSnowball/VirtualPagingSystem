#ifndef TEST_PAGE_TABLE_H_
#define TEST_PAGE_TABLE_H_


#include "../memorymanager/memory/page_table.h"

#include "../external/catch.hpp"

using namespace vmm::memory;
using namespace vmm_parameters;

TEST_CASE("Test page table", "[PageTable]") {
	
	SimulationParameters parameters;
	parameters.number_of_frames_ = 255;
	PageTable page_table(parameters.number_of_frames_);
	FrameNumber frame;
	PageTableResult code;

	page_table.GetEmpty(&frame);
	REQUIRE(frame == 0);

	code = page_table.GetFrame(1, &frame);
	REQUIRE(code == PageTableResult::kMiss);

	code = page_table.GetFrame(-2, &frame);
	REQUIRE(code == PageTableResult::kFailed);

	code = page_table.Update(1, 12);
	REQUIRE(code == PageTableResult::kSuccess);

	code = page_table.GetFrame(1, &frame);
	REQUIRE(code == PageTableResult::kHit);
	REQUIRE(frame == 12);

}
#endif