#ifndef PAGE_H_
#define PAGE_H_

#include <memory>

#include "..\..\utils\types.h"
#include "..\..\utils\parameters.h"


//depreciated and no longer included in design
namespace vmm {
namespace memory {
class Page {

public:
	Page();

	std::unique_ptr<Byte[]> data;
private:

};

} //end of namespace memory
} //end of namespace vmm

#endif
