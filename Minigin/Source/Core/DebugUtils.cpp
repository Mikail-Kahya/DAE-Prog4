#include "DebugUtils.h"

#include <windows.h>

void mk::Print(const std::string& text)
{
	OutputDebugString(text.c_str());
}
