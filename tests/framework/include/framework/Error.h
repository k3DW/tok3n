// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

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
