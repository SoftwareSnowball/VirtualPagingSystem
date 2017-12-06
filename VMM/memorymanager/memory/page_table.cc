#include "page_table.h"

namespace vmm {
namespace memory {

PageTable::PageTable(Count number_of_frames)
	:number_of_frames_(number_of_frames) {
	page_entries_ = PageEntries(new FrameNumber[number_of_frames_]);
}

PageTable::~PageTable()
{
}

PageReturn PageTable::GetFrame(PageNumber page_number, FrameNumber * frame)
{
	
	for (FrameNumber index = 0; index < number_of_frames_; index++) {
		if (page_entries_[index] == page_number) {
			*frame = index;
			return PageReturn::kHit;
		}
	}

	return PageReturn::kMiss;
}

PageReturn PageTable::GetEmpty(FrameNumber * frame)
{
	for (FrameNumber index = 0; index < number_of_frames_; index++) {
		if (page_entries_[index] == 0) {
			*frame = index;
			return PageReturn::kHit;
		}
	}

	return PageReturn::kMiss;
}

} //end of namespace memory
} //end of namespace vmm