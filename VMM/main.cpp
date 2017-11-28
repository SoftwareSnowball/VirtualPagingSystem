// VMM.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "parameters.h"

int main()
{
	std::cout << is_address_type_valid() << std::endl;
	std::cout << "Hello World!\n";

#ifdef _WIN32
	system("PAUSE");
#endif
    return 0;
}

