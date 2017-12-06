#include "page_table.h"

namespace vmm {
namespace memory {

PageTable::PageTable(Count number_of_frames)
	:number_of_frames_(number_of_frames) {
	page_entries_ = PageEntries(new FrameNumber[number_of_frames_]);

	memset(page_entries_.get(), -1, sizeof(FrameNumber) * number_of_frames_);
}

PageTable::~PageTable()
{
	page_entries_ = nullptr;
}

PageTableResult PageTable::GetFrame(PageNumber page_number, FrameNumber * frame)
{

	if (page_number < 0)
		return PageTableResult::kFailed;
	
	for (FrameNumber index = 0; index < number_of_frames_; index++) {
		if (page_entries_[index] == page_number) {
			*frame = index;
			return PageTableResult::kHit;
		}
	}

	return PageTableResult::kMiss;
}

PageTableResult PageTable::GetEmpty(FrameNumber * frame)
{
	for (FrameNumber index = 0; index < number_of_frames_; index++) {
		if (page_entries_[index] == -1) {
			*frame = index;
			return PageTableResult::kHit;
		}
	}

	return PageTableResult::kMiss;
}

} //end of namespace memory
} //end of namespace vmm