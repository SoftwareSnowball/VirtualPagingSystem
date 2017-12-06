#include "tlb.h"

namespace vmm {
namespace memory {

TLB::TLB(Count max_entries)
	:max_entries_(max_entries) {
	front_ = nullptr;
	back_ = nullptr;
	current_entries_;
}

TLB::~TLB() {
	front_ = nullptr;
	back_ = nullptr;
}

TLBResult TLB::GetFrame(PageNumber page_number, FrameNumber * frame) {
	if (page_number < 0 || frame == nullptr)
		return TLBResult::kFailed;

	TLBEntry* current = front_.get();
	TLBEntry* prev = nullptr;

	while (current) {
		if (current->page == page_number) {
			MoveToFront(current);
			*frame = current->frame;
			return TLBResult::kHit;

		current = current->next.get();
		}
	}
	return TLBResult::kMiss;
}

TLBResult TLB::Update(PageNumber page, FrameNumber frame) {
	if (page < 0 || frame < 0) {
		return TLBResult::kFailed;
	}

	std::shared_ptr<TLBEntry> entry(new TLBEntry);
	entry->frame = frame;
	entry->page = page;	

	return PushFront(std::move(entry));
}

TLBResult TLB::MoveToFront(TLBEntry* target) {
}

TLBResult TLB::PushFront(std::shared_ptr<TLBEntry> target) {

}

} //end of namespace memory
} //end of namespace vmm