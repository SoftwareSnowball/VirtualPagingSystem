#ifndef BACKINGSTORE_MANAGER_H_
#define BACKINGSTORE_MANAGER_H_

#include <string>

#include "..\..\utils\types.h"
#include "..\..\utils\parameters.h"
#include "..\memory\page.h"

namespace vmm {
namespace memory {

	enum struct BackingstoreReaderCode {
		kSuccess = 0,
		kIndexOutOfBounds,
		kFailed
	};


class BackingstoreManager {
public:
	BackingstoreManager(const vmm_parameters::SimulationParameters* parameters, std::string backingstore_path = std::string("BACKING_STORE"));
	~BackingstoreManager();

	BackingstoreReaderCode GetPage(PageNumber page_number, Byte* copy_location);

private:
	const vmm_parameters::SimulationParameters* parameters_;
	const std::string backingstore_path_;

};

} //end of namespace memory
} //end of namespace vmm




#endif

