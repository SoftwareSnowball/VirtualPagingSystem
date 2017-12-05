#include "fileio.h"
#include <fstream>


namespace vmm_io {

	IOStatus FileIO::ReadAddresses(std::string path, std::vector<LogicalAddress>* addresses) {
		std::ifstream reader(path);
		if (!reader.is_open())
			return IOStatus(kFileCannotBeOpened);

		std::string line;

		LogicalAddress element;

		while (!reader.eof())
		{
			std::getline(reader, line);

			//AddressType could change in size, so the string is initially
			//converted to a long long to prevent data loss if the simulation is set
			//to use a very large address. 
			if (!line.empty()) {
			element = (LogicalAddress)std::atoll(line.c_str());
			addresses->push_back(element);
			}
		}

		reader.close();
		return IOStatus(kSuccess);
	}

	IOStatus FileIO::WriteFile(std::string path, std::string data)
	{
		std::ofstream writer(path);

		if (!writer.is_open()) {
			return IOStatus(kFileCannotBeOpened);
		}

		writer << data;

		writer.close();
		return IOStatus(kSuccess);
	}


} //end of namespace vmm_io