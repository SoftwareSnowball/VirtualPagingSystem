#ifndef MAIN_MEMORY_H_
#define MAIN_MEMORY_H_

#include "types.h"
#include "parameters.h"
#include "page.h"

namespace vmm {
namespace data {

	//Do not put this on the stack. It is going to be way too large.
	class PhysicalMemory {
	public:
		PhysicalMemory();
		~PhysicalMemory();

		Byte getFromAddress(AddressType page_location, AddressType offset);
		Byte setPage(AddressType page_location, void* page); //TODO: replace void with page class when it exists

	private:
		union {
			Byte data_[NUMBER_OF_PAGES * NUMBER_OF_FRAMES];
			Page pages_[NUMBER_OF_PAGES];
		};
	};


}//end of namespace data
} //end of namespace vmm



#endif
