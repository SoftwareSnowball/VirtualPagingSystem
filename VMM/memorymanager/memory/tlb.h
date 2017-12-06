#ifndef TLB_H_
#define TLB_H_

#include <memory>
#include "..\..\utils\types.h"


namespace vmm {
namespace memory {

enum struct TLBResult {
	kHit,
	kMiss,
	kFailed,
	kSuccess
};

struct TLBEntry {
	PageNumber page;
	FrameNumber frame;
	std::shared_ptr<TLBEntry> next;
	std::weak_ptr<TLBEntry> prev;
};

class TLB {
public:
	TLB(Count max_entries);
	~TLB();

	TLBResult GetFrame(PageNumber page_number, FrameNumber* frame);
	TLBResult Update(PageNumber page, FrameNumber frame);

private:
	TLBResult MoveToFront(TLBEntry* target);
	TLBResult PushFront(std::shared_ptr<TLBEntry> target);

private:
	Count current_entries_;
	const Count max_entries_;
	
	std::shared_ptr<TLBEntry> front_;
	std::shared_ptr<TLBEntry> back_;
};


} //end of namespace memory
} //end of namespace vmm


#endif
