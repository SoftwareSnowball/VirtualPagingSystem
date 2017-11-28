#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

//Simulation Parameters

#define PAGE_TABLE_SIZE_BITS	8
#define PAGE_SIZE_BITS			8

#define ADDRESS_SIZE			PAGE_SIZE_BITS + PAGE_TABLE_SIZE_BITS //should be a power of two
using address_type = int;		//IF THIS IS SET TOO SMALL FOR THE ADDRESS SIZE IT WILL BREAK THINGS

#define PAGE_SIZE				1 << PAGE_SIZE_BITS
#define NUMBER_PAGES			1 << PAGE_TABLE_SIZE_BITS


//Validity Checks

constexpr bool is_address_type_valid()
{
	if (ADDRESS_SIZE > (sizeof(address_type) * 8))
		return false;

	return true;
}

static_assert(is_address_type_valid(), "Address is too large for selected address variable type");


#endif
