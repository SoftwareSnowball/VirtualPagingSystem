#ifndef MAIN_MEMORY_H_
#define MAIN_MEMORY_H_

#include <memory>

namespace vmm {
namespace memory {

class MainMemory {
public:


private:
	std::unique_ptr<Byte[]> data;

};

} //end of namespace memory
} //end of namespace vmm

#endif