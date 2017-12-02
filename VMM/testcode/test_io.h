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
			should return kFileDoesNotExist  (enum IOStatus)
		file cannot be opened:
			should return kFileCannotBeOpened (enum IOStatus)
		Vector Pointer is Null:
			returns kInvalidInput (enum IOStatus)
		Vector Pointer is wild:
			cannot detect this error. Program will crash.

writeString
	Purpose:
		This method writes a string to file
	Inputs
		string with file path

	Outputs:
		returns kSuccess if it works
		return kFileCannotBeOpened if failed

*/


#include "../external/catch.hpp"
#include ""
using namespace vmm;
using namespace io;





#endif

