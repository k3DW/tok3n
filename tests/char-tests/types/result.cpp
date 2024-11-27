// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.h"

using namespace k3::tok3n::detail;

FIXTURE("result");

TEST("result", "result_of result<void>")
{
	using R = result<void, value_type>;

	ASSERT_CONCEPT    (result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<int>, value_type);
}

TEST("result", "result_of result<int>")
{
	using R = result<int, value_type>;

	ASSERT_NOT_CONCEPT(result_of, R, void, value_type);
	ASSERT_CONCEPT    (result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(result_of, R, int&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, int&&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, const int&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, const int&&, value_type);
}

TEST("result", "result_of result<std::pair>")
{
	using R = result<std::pair<int, double>, value_type>;

	ASSERT_NOT_CONCEPT(result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, int, value_type);
	ASSERT_CONCEPT    (result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(result_of, R, std::pair<int, double>&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<int, double>&&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, const std::pair<int, double>&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, const std::pair<int, double>&&, value_type);
}

TEST("result", "result_of result<std::string>")
{
	using R = result<std::string, value_type>;

	ASSERT_NOT_CONCEPT(result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<int, double>, value_type);
	ASSERT_CONCEPT    (result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(result_of, R, std::string&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::string&&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, const std::string&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, const std::string&&, value_type);
}

TEST("result", "result_of result<std::vector>")
{
	using R = result<std::vector<int>, value_type>;

	ASSERT_NOT_CONCEPT(result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::string, value_type);
	ASSERT_CONCEPT    (result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(result_of, R, std::vector<int>&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<int>&&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, const std::vector<int>&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, const std::vector<int>&&, value_type);
}

TEST("result", "result_of result<std::unique_ptr>")
{
	using R = result<std::unique_ptr<int>, value_type>;

	ASSERT_NOT_CONCEPT(result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<int>, value_type);
	ASSERT_CONCEPT    (result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<int>&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<int>&&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, const std::unique_ptr<int>&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, const std::unique_ptr<int>&&, value_type);
}

TEST("result", "result_of result<MoveOnlyWrapper>")
{
	using R = result<MoveOnlyWrapper<int>, value_type>;

	ASSERT_NOT_CONCEPT(result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_CONCEPT    (result_of, R, MoveOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<int>&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, MoveOnlyWrapper<int>&&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, const MoveOnlyWrapper<int>&, value_type);
	ASSERT_NOT_CONCEPT(result_of, R, const MoveOnlyWrapper<int>&&, value_type);
}
