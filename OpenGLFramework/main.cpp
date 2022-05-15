#include <iostream>
#include "CExample01.h"

int main()
{
	CExample01 myapp;
	if (!myapp.createWindow("Hello", 800, 600))
	{
		std::cout << "Error creating window" << std::endl;
		return 1;
	}

	myapp.runApp();

	return 0;
}