#ifndef PAGE_H_
#define PAGE_H_

#include "types.h"
#include "parameters.h"

namespace vmm {
namespace data {

	struct Page {
		Byte page_data_[PAGE_SIZE];
	};

} //end of namespace data	
} //end of namespace vmm





#endif
