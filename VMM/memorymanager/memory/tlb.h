#ifndef TLB_H_
#define TLB_H_

#include <list>
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
	TLBEntry() {};
	TLBEntry(PageNumber page, FrameNumber frame) :page(page), frame(frame) {};
	PageNumber page;
	FrameNumber frame;
};

class TLB {
public:
	TLB(Count max_entries);
	~TLB();

	TLBResult GetFrame(PageNumber page_number, FrameNumber* frame);
	TLBResult Update(PageNumber page, FrameNumber frame);

private:
	TLBResult MoveToFront(TLBEntry* target);
	TLBResult PushFront(int target);

private:
	const Count max_entries_;
	std::list<TLBEntry> entries_;
};


} //end of namespace memory
} //end of namespace vmm


#endif
