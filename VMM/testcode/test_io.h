#ifndef TEST_DATA_H_
#define TEST_DATA_H_

/*
Module:	FileIO
Purpose: read and write integers from text files (does not deal with backing store)
Methods:
	readInts
	writeString

readAddresses
	Purpose:
		This method shall read a file of line delineated addresses

	Inputs:
		string file_path
		Address Vector Pointer

	outputs:
		vector of addresses (by reference)
		exit code (integer with some status message)

	If Successful:
		returns Success (enum IOStatus)
		

	Sad Paths:
		file data does not represent an integer:
			perform type cast and ignore error (#quality)
		file does not exits:
			should return kFileCannotBeOpened (enum IOStatus)
		Vector Pointer is Null:
			returns kInvalidInput (enum IOStatus)
		Vector Pointer is wild:
			cannot detect this error. Program will crash.

writeData
	Purpose:
		This method writes a string of data to a file
	Inputs
		string with file path
		string with data

	Outputs:
		returns kSuccess if it works
		return kFileCannotBeOpened if failed

*/

#include "../external/catch.hpp"
#include "../io/fileio.h"
using namespace vmm_io;

TEST_CASE("Test IO_MANAGER ReadAddresses", "[FileIO]") {
	FileIO io_manager;
	IOStatus status;
	std::vector<AddressType> addresses;
	std::string path = "testinput.txt";
	std::string badPath = "whatIsThis.txt";

	SECTION("Check ReadAddresses Interface") {
		status = io_manager.ReadAddresses(path, &addresses);

		REQUIRE(status == kSuccess);
	}

	SECTION("Check ReadAddresses with bad file") {
		status = io_manager.ReadAddresses(badPath, &addresses);

		REQUIRE(status == kFileCannotBeOpened);
	}

	SECTION("Check ReadAddresses can read test file") {
		status = io_manager.ReadAddresses(path, &addresses);

		AddressType file_contents[] = { 3, 259, 515, 771, 1027,
			1283, 7, 263, 519, 775, 1031, 1287 };
		int file_length = sizeof(file_contents) / sizeof(AddressType);

		REQUIRE(addresses.size() == file_length);

		for (int i = 0; i < addresses.size(); i++) {
			REQUIRE(addresses[i] == file_contents[i]);
		}
		
	}
}

TEST_CASE("Test IO_MANAGER WriteFile", "[FileIO]") {
	FileIO io_manager;
	IOStatus status;
	std::string path = "sampleOutput.txt";
	std::string output_data = "Hello World\nNew line of stuff!";

	SECTION("Testing output with simple string") {
		status = io_manager.WriteFile(path, output_data);
		REQUIRE(status == kSuccess);
	}
}



#endif

