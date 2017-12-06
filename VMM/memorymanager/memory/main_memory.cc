#include "main_memory.h"

namespace vmm {
namespace memory {

MainMemory::MainMemory(Size frame_size, Count number_of_frames)
	:frame_size_(frame_size), number_of_frames_(number_of_frames) {
	data_ = std::unique_ptr<Byte[]>(new Byte[frame_size_ * number_of_frames_]);

}

MainMemory::~MainMemory()
{
}

Byte* MainMemory::getFrameAddress(FrameNumber frame)
{
	if (frame >= number_of_frames_)
		return nullptr;

	Byte* frameptr = data_.get();
	frameptr += frame * frame_size_;

	return frameptr;
}

} //end of namespace memory
} //end of namespace vmm