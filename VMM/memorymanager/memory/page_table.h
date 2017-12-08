#ifndef PAGE_TABLE_H_
#define PAGE_TABLE_H_

#include <memory>

#include "../../utils/types.h"
#include "../../utils/parameters.h"


namespace vmm {
namespace memory {

using PageEntries = std::unique_ptr<PageNumber[]>;

enum struct PageTableResult {
	kHit,
	kMiss,
	kFailed,
	kSuccess
};

class PageTable {
public:
	PageTable(Count number_of_frames);
	~PageTable();

	PageTableResult GetFrame(PageNumber page_number, FrameNumber* frame);
	PageTableResult GetEmpty(FrameNumber* frame);
	PageTableResult Update(PageNumber page, FrameNumber frame);

private:
	const Count number_of_frames_;
	PageEntries page_entries_;
};

} //end of namespace memory
} //end of namespace vmm



#endif