#include "DebugUtils.h"

#ifdef WIN32
#include <windows.h>
#else
#include <iostream>
#endif

void mk::Print(const std::string& text)
{
#ifdef WIN32
	OutputDebugString(text.c_str());
#else
	std::cout << text << std::endl;
#endif
}
