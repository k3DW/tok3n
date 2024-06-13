#include "pch.h"
#include "enum-tests/samples.h"

FIXTURE("Result");

TEST("Result", "IsResult Result<void>")
{
	using R = Result<void, E>;

	ASSERT_CONCEPT    (IsResult, R, void, E);
	ASSERT_NOT_CONCEPT(IsResult, R, int, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, E);
}

TEST("Result", "IsResult Result<int>")
{
	using R = Result<int, E>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, E);
	ASSERT_CONCEPT    (IsResult, R, int, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, double, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, int&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, int&&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&&, E);
}

TEST("Result", "IsResult Result<std::pair>")
{
	using R = Result<std::pair<int, double>, E>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, E);
	ASSERT_NOT_CONCEPT(IsResult, R, int, E);
	ASSERT_CONCEPT    (IsResult, R, std::pair<int, double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, double, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&&, E);
}

TEST("Result", "IsResult Result<std::string>")
{
	using R = Result<std::string, E>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, E);
	ASSERT_NOT_CONCEPT(IsResult, R, int, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, E);
	ASSERT_CONCEPT    (IsResult, R, std::string, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, double, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, std::string&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string&&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&&, E);
}

TEST("Result", "IsResult Result<std::vector>")
{
	using R = Result<std::vector<int>, E>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, E);
	ASSERT_NOT_CONCEPT(IsResult, R, int, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, E);
	ASSERT_CONCEPT    (IsResult, R, std::vector<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, double, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&&, E);
}

TEST("Result", "IsResult Result<std::unique_ptr>")
{
	using R = Result<std::unique_ptr<int>, E>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, E);
	ASSERT_NOT_CONCEPT(IsResult, R, int, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, E);
	ASSERT_CONCEPT    (IsResult, R, std::unique_ptr<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, double, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&&, E);
}

TEST("Result", "IsResult Result<MoveOnlyWrapper>")
{
	using R = Result<MoveOnlyWrapper<int>, E>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, E);
	ASSERT_NOT_CONCEPT(IsResult, R, int, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, E);
	ASSERT_CONCEPT    (IsResult, R, MoveOnlyWrapper<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, double, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&&, E);
}

TEST("Result", "IsResult Result<CopyOnlyWrapper>")
{
	using R = Result<CopyOnlyWrapper<int>, E>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, E);
	ASSERT_NOT_CONCEPT(IsResult, R, int, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, E);
	ASSERT_CONCEPT    (IsResult, R, CopyOnlyWrapper<int>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, double, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, E);

	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&, E);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&&, E);
}
