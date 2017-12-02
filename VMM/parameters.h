#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include "types.h"
//Yes I included a header file in a header file. I do not enjoy the "guess which header file this header
//file depends on" game.

namespace vmm {

namespace parameters {

#if 1
	const PageNumber NUMBER_OF_PAGES = 256;
	const FrameNumber NUMBER_OF_FRAMES = 256;

	const unsigned int PAGE_TABLE_SIZE_BITS = 8; //TODO: change type and make these dependent on NUMBER_OF_PAGES etc.
	const unsigned int PAGE_SIZE_BITS = 8;

	const unsigned int ADDRESS_SIZE = PAGE_TABLE_SIZE_BITS + PAGE_SIZE_BITS;

	const unsigned int PAGE_SIZE = 1 << PAGE_SIZE_BITS;
	const unsigned int NUMBER_OF_PAGES = 1 << PAGE_TABLE_SIZE_BITS;

#else
	//Simulation Parameters

	#define NUMBER_OF_PAGES 256
	#define NUMBER_OF_FRAMES 256
	
	#define PAGE_TABLE_SIZE_BITS	8
	#define PAGE_SIZE_BITS			8
	
	#define ADDRESS_SIZE			PAGE_SIZE_BITS + PAGE_TABLE_SIZE_BITS //should be a power of two
		
	#define PAGE_SIZE				1 << PAGE_SIZE_BITS
	#define NUMBER_PAGES			1 << PAGE_TABLE_SIZE_BITS
	
	
	//Validity Checks (These will need to change if we stop using defines or global consts)
	
	constexpr bool is_address_type_valid() {
		if (ADDRESS_SIZE > (sizeof(AddressType) * 8))
			return false;
	
		return true;
	}
	static_assert(is_address_type_valid(), "Address is too large for selected address variable type");
	

	constexpr bool is_max_frame_number_valid() {
		if (NUMBER_OF_FRAMES < NUMBER_OF_PAGES)
			return false;

		return true;
	}
	static_assert(is_max_frame_number_valid(), "The maximum number of frames should not be less than the number of pages");

#endif
	
} //end of namespace parameters
} //end of namespace vmm


#endif
