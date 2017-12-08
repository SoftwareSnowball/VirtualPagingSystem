/*
Author:			James Malloy
file:			main.cpp
Project:		Virtual Memory Manager (Project 5 COMP3500)
Date Created:	11/30/2017
Last Change:	12/1/2017

Purpose:	
	This file holds the entry point for the virtual memory manager application


References:
https://stackoverflow.com/questions/191757/how-to-concatenate-a-stdstring-and-an-int
https://stackoverflow.com/questions/17045493/default-int-main-arguments-in-c-c
https://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function
http://www.cplusplus.com/reference/istream/istream/getline/
http://www.cplusplus.com/reference/string/string/reserve/
https://stackoverflow.com/questions/191757/how-to-concatenate-a-stdstring-and-an-int
http://en.cppreference.com/w/cpp/memory/unique_ptr
http://www.cplusplus.com/reference/list/list/
http://www.cplusplus.com/reference/string/string/append/
https://stackoverflow.com/questions/26473733/using-smart-pointers-as-a-class-member
https://stackoverflow.com/questions/10532661/strange-segfault-with-unique-ptr-and-shared-ptr
http://www.cplusplus.com/forum/general/147341/ (enum vs enum class)
http://www.cplusplus.com/reference/vector/vector/
http://www.cplusplus.com/reference/string/stoll/
*/



// Note that my test code depends on the catch library at
// https://github.com/catchorg/Catch2
// This dependency is only in my test code. My production code only depends
// on standard c++ libraries
#define RUN_TEST_CODE 1
#if RUN_TEST_CODE
#include "testcode\testcode.h"
#else

#include <iostream>
#include <vector>

#include "utils\parameters.h"
#include "memorymanager\memory_manager.h"
#include "io\fileio.h"


//for questions on args to main function

int main(int arg_count, const char* arg_val[])
{

	std::string file_path;
	std::string output_file("output.txt");
	char line[64];
	
	if (arg_count < 2) {
		std::cout << "Please input the path to a file with input addresses.\n";
		std::cin.getline(line, sizeof(line));
		file_path = std::string(line);
	}
	else {
		file_path = std::string(arg_val[1]);
	}

	vmm_io::FileIO file_manager;
	vmm::ParametersManagedPtr parameters(new vmm_parameters::SimulationParameters);
	vmm::MemoryManager memory_manager(std::move(parameters));

	std::string parameter_summary;
	memory_manager.GetParameterSummary(&parameter_summary);

	std::cout << parameter_summary << std::endl;

	bool valid_input;;
	bool display_physical_address;

	//output simulation characteristics
	valid_input = false;
	while (!valid_input) {
		std::cout << "Display physical address [y or n] ";
		std::cin.getline(line, sizeof(line));
		valid_input = line[0] == 'y' || line[0] == 'n';
		display_physical_address = line[0] == 'y';
	}

	valid_input = false;
	while (!valid_input) {
		std::cout << "Choose TLB Replacement Strategy [1:FIFO, 2: LRU] ";
		std::cin.getline(line, sizeof(line));	
		valid_input = memory_manager.SetTLBReplacementPolicy(line[0]) == vmm::MemoryManagerResult::kSuccess;
	}

	std::vector<LogicalAddress> logic_addresses;


	if (file_manager.ReadAddresses(file_path, &logic_addresses) != vmm_io::IOStatus::kSuccess) {
		std::cout << "Could not open file " << file_path << std::endl;
		return 0;
	}

	std::string results;
	results.reserve(logic_addresses.size() * 15);

	vmm::MemoryManagerResult read_result;
	Byte value;
	PhyscialAddress phy_addr;

	for (unsigned int i = 0; i < logic_addresses.size(); i++) {

		read_result = memory_manager.ReadAddress(logic_addresses[i], &value, &phy_addr);

		results.append("Virtual Address: ");
		results.append(std::to_string(logic_addresses[i]));

		if (read_result == vmm::MemoryManagerResult::kSuccess) {
			if (display_physical_address)
				results += "; Physical Address: " + std::to_string(phy_addr);
			results += "; Value: " + std::to_string((unsigned short int)value);
		}
		else {
			results.append("Read operation failed: ");
			results.append(memory_manager.GetErrorMessage());
		}
			results.append("\n");
	}

	std::cout << results;
	file_manager.WriteFile(output_file, results);
	std::cout << "results were stored in " << output_file << std::endl;

    return 0;
}


#endif

