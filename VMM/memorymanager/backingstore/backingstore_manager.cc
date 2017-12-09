#include "backingstore_manager.h"

#include <fstream>
#include <cstring>

namespace vmm {
namespace memory {

BackingstoreManager::BackingstoreManager(const vmm_parameters::SimulationParameters * parameters, std::string backingstore_path)
		:parameters_(parameters),
		backingstore_path_(backingstore_path) {

}

BackingstoreManager::~BackingstoreManager() {
	return;
}

BackingstoreReaderCode BackingstoreManager::GetPage(PageNumber page_number, Byte* copy_location)
{
	int start_location = parameters_->page_size_ * page_number;

	std::ifstream backingstore(backingstore_path_, std::ios::binary);

	if (backingstore.fail())
	{
		std::string exceptionMsg = "Backingstore cannot be opened at location ";
		return BackingstoreReaderCode::kFailed;
	}

	backingstore.seekg(start_location, std::ios::beg);
	backingstore.read((char*)copy_location, parameters_->page_size_);

	if (backingstore.fail())
	{
		memset(copy_location, 0, parameters_->page_size_);
		return BackingstoreReaderCode::kIndexOutOfBounds;
	}


	backingstore.close();
	return BackingstoreReaderCode::kSuccess;
}

Size BackingstoreManager::GetBackingStoreSize()
{
	std::ifstream backingstore(backingstore_path_, std::ios::binary);
	if (backingstore.fail())
	{
		std::string exceptionMsg = "Backingstore cannot be opened at location ";
		return 0;
	}
	

	return backingstore.end;
}





} //end of namespace memory
} //end of namespace vmm