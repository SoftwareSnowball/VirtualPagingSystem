/*
Author:			James Malloy
file:			main.cpp
Project:		Virtual Memory Manager (Project 5 COMP3500)
Date Created:	11/30/2017
Last Change:	12/1/2017

Purpose:	
	This file holds the entry point for the 
			



*/

#include <iostream>
#include "parameters.h"

// Note that my test code depends on the catch library at
// https://github.com/catchorg/Catch2
// This dependency is only in my test code. My production code only depends
// on standard c++ libraries
#define UNIT_TEST_CONFIGURATION 0
#if UNIT_TEST_CONFIGURATION 
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

