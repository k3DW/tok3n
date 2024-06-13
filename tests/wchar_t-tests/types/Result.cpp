#include "pch.h"
#include "wchar_t-tests/samples.h"

FIXTURE("Result");

TEST("Result", "IsResult Result<void>")
{
	using R = Result<void, wchar_t>;

	ASSERT_CONCEPT    (IsResult, R, void, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, int, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, wchar_t);
}

TEST("Result", "IsResult Result<int>")
{
	using R = Result<int, wchar_t>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, wchar_t);
	ASSERT_CONCEPT    (IsResult, R, int, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, double, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, int&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, int&&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&&, wchar_t);
}

TEST("Result", "IsResult Result<std::pair>")
{
	using R = Result<std::pair<int, double>, wchar_t>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, int, wchar_t);
	ASSERT_CONCEPT    (IsResult, R, std::pair<int, double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, double, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&&, wchar_t);
}

TEST("Result", "IsResult Result<std::string>")
{
	using R = Result<std::string, wchar_t>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, int, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, wchar_t);
	ASSERT_CONCEPT    (IsResult, R, std::string, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, double, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, std::string&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string&&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&&, wchar_t);
}

TEST("Result", "IsResult Result<std::vector>")
{
	using R = Result<std::vector<int>, wchar_t>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, int, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, wchar_t);
	ASSERT_CONCEPT    (IsResult, R, std::vector<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, double, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&&, wchar_t);
}

TEST("Result", "IsResult Result<std::unique_ptr>")
{
	using R = Result<std::unique_ptr<int>, wchar_t>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, int, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, wchar_t);
	ASSERT_CONCEPT    (IsResult, R, std::unique_ptr<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, double, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&&, wchar_t);
}

TEST("Result", "IsResult Result<MoveOnlyWrapper>")
{
	using R = Result<MoveOnlyWrapper<int>, wchar_t>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, int, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, wchar_t);
	ASSERT_CONCEPT    (IsResult, R, MoveOnlyWrapper<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, double, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&&, wchar_t);
}

TEST("Result", "IsResult Result<CopyOnlyWrapper>")
{
	using R = Result<CopyOnlyWrapper<int>, wchar_t>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, int, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, wchar_t);
	ASSERT_CONCEPT    (IsResult, R, CopyOnlyWrapper<int>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, double, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, wchar_t);

	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&, wchar_t);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&&, wchar_t);
}
