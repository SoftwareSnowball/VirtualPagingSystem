#ifndef PAGE_TABLE_H_
#define PAGE_TABLE_H_

#include "parameters.h"

namespace data {



	class PageTable
	{
	public:
		PageTable() = default;
		~PageTable() = default;

		parameters::AddressType getPageOffset(parameters::AddressType page_number); //TODO: find the right word for this

	private:

		//TODO:put data here


	};

} //end of namespace data

#endif
