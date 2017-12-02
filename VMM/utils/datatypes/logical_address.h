#ifndef LOGICAL_ADDRESS_H_
#define LOGICAL_ADDRESS_H_

#include "../utils/types.h"

namespace vmm {
namespace data {


	class LogicalAddress {
	public:
		LogicalAddress(AddressType address);
		~LogicalAddress();

		PageNumber getPageNumber();
		AddressType getOffset();
		AddressType getAddress();

	private:
		AddressType address_;

	};



} //end of namespace data
} //end of namespace vmm



#endif
