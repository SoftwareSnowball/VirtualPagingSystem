#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include "types.h"
//Yes I included a header file in a header file. I do not enjoy the "guess which header file this header
//file depends on" game.

namespace parameters {
	//Simulation Parameters

#define NUMBER_OF_PAGES 256
#define NUMBER_OF_FRAMES 256
	
	#define PAGE_TABLE_SIZE_BITS	8
	#define PAGE_SIZE_BITS			8
	
	#define ADDRESS_SIZE			PAGE_SIZE_BITS + PAGE_TABLE_SIZE_BITS //should be a power of two
	
	
	#define PAGE_SIZE				1 << PAGE_SIZE_BITS
	#define NUMBER_PAGES			1 << PAGE_TABLE_SIZE_BITS
	
	
	//Validity Checks
	
	constexpr bool is_address_type_valid() {
		if (ADDRESS_SIZE > (sizeof(AddressType) * 8))
			return false;
	
		return true;
	}
	
	static_assert(is_address_type_valid(), "Address is too large for selected address variable type");
	
	
} //end of namespace parameters

#endif
