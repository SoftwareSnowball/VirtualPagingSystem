#ifndef FILE_IO_H_
#define FILE_IO_H_

#include <string>
#include <vector>
#include "../utils/types.h"

namespace vmm_io {

	enum IOStatus {
		kSuccess = 0,
		kFileNotFound = 1,
		kFileCannotBeOpened = 2,
		kInvalidInput = 3
	};

	class FileIO {
	public:
		FileIO() = default;
		~FileIO() = default;

		IOStatus ReadAddresses(std::string path, std::vector<AddressType>* addresses);
		IOStatus WriteFile(std::string path, std::string data);

	};


} //end of namespace vmm_io

#endif