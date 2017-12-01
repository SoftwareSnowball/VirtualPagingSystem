// VMM.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "parameters.h"

#define UNIT_TEST_CONFIGURATION 0
#if UNIT_TEST_CONFIGURATION 
#define CATCH_CONFIG_MAIN
#include "external\catch.hpp"
#include "testcode\testcode.h"
#else

int main()
{


#ifdef _WIN32
	system("PAUSE");
#endif
    return 0;
}


#endif

