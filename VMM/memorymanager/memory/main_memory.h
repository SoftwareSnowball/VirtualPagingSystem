#ifndef MAIN_MEMORY_H_
#define MAIN_MEMORY_H_

#include <memory>

#include "..\..\utils\types.h"
#include "..\..\utils\parameters.h"

namespace vmm {
namespace memory {

class MainMemory {
public:
	MainMemory(Size frame_size, Count number_of_frames);
	~MainMemory();

	Byte* GetFrameAddress(FrameNumber frame);

private:
	const Size frame_size_;
	const Count number_of_frames_;
	std::unique_ptr<Byte[]> data_;

};

} //end of namespace memory
} //end of namespace vmm

#endif