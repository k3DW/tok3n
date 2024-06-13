#include "integral-tests/samples.h"

FIXTURE("Result");

TEST("Result", "IsResult Result<void>")
{
	using R = Result<void, value_type>;

	ASSERT_CONCEPT    (IsResult, R, void, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, int, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, value_type);
}

TEST("Result", "IsResult Result<int>")
{
	using R = Result<int, value_type>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, value_type);
	ASSERT_CONCEPT    (IsResult, R, int, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, double, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, int&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, int&&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&&, value_type);
}

TEST("Result", "IsResult Result<std::pair>")
{
	using R = Result<std::pair<int, double>, value_type>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, int, value_type);
	ASSERT_CONCEPT    (IsResult, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, double, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&&, value_type);
}

TEST("Result", "IsResult Result<std::string>")
{
	using R = Result<std::string, value_type>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, int, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, value_type);
	ASSERT_CONCEPT    (IsResult, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, double, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, std::string&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string&&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&&, value_type);
}

TEST("Result", "IsResult Result<std::vector>")
{
	using R = Result<std::vector<int>, value_type>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, int, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, value_type);
	ASSERT_CONCEPT    (IsResult, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, double, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&&, value_type);
}

TEST("Result", "IsResult Result<std::unique_ptr>")
{
	using R = Result<std::unique_ptr<int>, value_type>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, int, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, value_type);
	ASSERT_CONCEPT    (IsResult, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, double, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&&, value_type);
}

TEST("Result", "IsResult Result<MoveOnlyWrapper>")
{
	using R = Result<MoveOnlyWrapper<int>, value_type>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, int, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, value_type);
	ASSERT_CONCEPT    (IsResult, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, double, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&&, value_type);
}

TEST("Result", "IsResult Result<CopyOnlyWrapper>")
{
	using R = Result<CopyOnlyWrapper<int>, value_type>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, int, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_CONCEPT    (IsResult, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, double, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&, value_type);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&&, value_type);
}
