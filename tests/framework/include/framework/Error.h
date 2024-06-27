#pragma once
#include <source_location>
#include <string_view>

struct Error
{
	enum class Time
	{
		compile_time,
		run_time,
	};
	enum class Fatality
	{
		non_fatal,
		fatal,
	};
	
	Time time;
	Fatality fatality;
	std::string_view message;
	std::source_location location;
};

void print(std::ostream& os, const Error& error);
