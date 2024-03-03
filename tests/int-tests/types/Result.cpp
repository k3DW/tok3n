#include "pch.h"
#include "int-samples/int-samples.h"

FIXTURE("Result");

TEST("Result", "IsResult Result<void>")
{
	using R = Result<void, int>;

	ASSERT_CONCEPT    (IsResult, R, void, int);
	ASSERT_NOT_CONCEPT(IsResult, R, int, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, int);
}

TEST("Result", "IsResult Result<int>")
{
	using R = Result<int, int>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, int);
	ASSERT_CONCEPT    (IsResult, R, int, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, double, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, int&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, int&&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&&, int);
}

TEST("Result", "IsResult Result<std::pair>")
{
	using R = Result<std::pair<int, double>, int>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, int);
	ASSERT_NOT_CONCEPT(IsResult, R, int, int);
	ASSERT_CONCEPT    (IsResult, R, std::pair<int, double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, double, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&&, int);
}

TEST("Result", "IsResult Result<std::string>")
{
	using R = Result<std::string, int>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, int);
	ASSERT_NOT_CONCEPT(IsResult, R, int, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, int);
	ASSERT_CONCEPT    (IsResult, R, std::string, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, double, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, std::string&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string&&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&&, int);
}

TEST("Result", "IsResult Result<std::vector>")
{
	using R = Result<std::vector<int>, int>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, int);
	ASSERT_NOT_CONCEPT(IsResult, R, int, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, int);
	ASSERT_CONCEPT    (IsResult, R, std::vector<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, double, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&&, int);
}

TEST("Result", "IsResult Result<std::unique_ptr>")
{
	using R = Result<std::unique_ptr<int>, int>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, int);
	ASSERT_NOT_CONCEPT(IsResult, R, int, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, int);
	ASSERT_CONCEPT    (IsResult, R, std::unique_ptr<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, double, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&&, int);
}

TEST("Result", "IsResult Result<MoveOnlyWrapper>")
{
	using R = Result<MoveOnlyWrapper<int>, int>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, int);
	ASSERT_NOT_CONCEPT(IsResult, R, int, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, int);
	ASSERT_CONCEPT    (IsResult, R, MoveOnlyWrapper<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, double, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&&, int);
}

TEST("Result", "IsResult Result<CopyOnlyWrapper>")
{
	using R = Result<CopyOnlyWrapper<int>, int>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, int);
	ASSERT_NOT_CONCEPT(IsResult, R, int, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, int);
	ASSERT_CONCEPT    (IsResult, R, CopyOnlyWrapper<int>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, double, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, int);

	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&, int);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&&, int);
}
