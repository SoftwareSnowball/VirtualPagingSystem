#ifndef TEST_TLB_H_
#define TEST_TLB_H_

#include "..\memorymanager\memory\tlb.h"
#include "..\external\catch.hpp"

using namespace vmm::memory;

TEST_CASE("Testing TLB", "[TLB]") {
	TLB tlb(5);
	FrameNumber frame;
	TLBResult result;

	tlb.Update(1, 1);
	tlb.Update(2, 2);
	tlb.Update(3, 3);
	tlb.Update(4, 4);
	tlb.Update(5, 5);
	tlb.Update(6, 6);


	SECTION("Test 1") {
		result = tlb.GetFrame(1, &frame);
		REQUIRE(result == TLBResult::kMiss);
	}

	SECTION("Test 2") {
		result = tlb.GetFrame(2, &frame);
		REQUIRE(result == TLBResult::kHit);
		REQUIRE(frame == 2);
	}

	SECTION("Test 3") {
		tlb.Update(7, 7);
		result = tlb.GetFrame(2, &frame);
		REQUIRE(result == TLBResult::kMiss);
		result = tlb.GetFrame(7, &frame);
		REQUIRE(result == TLBResult::kHit);
		REQUIRE(frame == 7);
	}

	SECTION("Test 4") {
		result = tlb.Update(-7, 7);
		REQUIRE(result == TLBResult::kFailed);
		result = tlb.GetFrame(-7, &frame);
		REQUIRE(result == TLBResult::kFailed);
	}

}




#endif
