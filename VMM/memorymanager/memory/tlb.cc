#include "tlb.h"

namespace vmm {
namespace memory {

TLB::TLB(Count max_entries, bool use_tlb)
	:max_entries_(max_entries), use_lru_(use_tlb) {
}

TLB::~TLB() {

}

TLBResult TLB::GetFrame(PageNumber page_number, FrameNumber * frame) {
	
	if (page_number < 1)
		return TLBResult::kFailed;
	
	auto itr = entries_.begin();
	for (auto itr = entries_.begin(); itr != entries_.end(); itr++) {

		if (itr->page == page_number)
		{
			*frame = itr->frame;
			if (use_lru_)
				entries_.splice(entries_.begin(), entries_, itr); //move element to front

			return TLBResult::kHit;
		}
	}
	return TLBResult::kMiss;
}

TLBResult TLB::Update(PageNumber page, FrameNumber frame) {

	if (page < 0 || frame < 0) 
		return TLBResult::kFailed;

	TLBEntry entry;
	entry.frame = frame;
	entry.page = page;

	entries_.push_front(std::move(entry));
	
	if (entries_.size() > max_entries_) {
		auto end = entries_.end();
		entries_.erase(--end);
	}
	
	return TLBResult::kSuccess;
}

TLBResult TLB::EnableLRU() {
	use_lru_ = true;
	return TLBResult::kSuccess;
}

TLBResult TLB::DisableLRU()
{
	use_lru_ = false;
	return TLBResult::kSuccess;
}


} //end of namespace memory
} //end of namespace vmm