#pragma once
#include <source_location>
#include <string_view>

struct Error
{
	std::string_view Message;
	std::source_location Location;
};
