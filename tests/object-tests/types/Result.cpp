#include "samples.h"

FIXTURE("Result");

TEST("Result", "IsResult Result<void>")
{
	using R = Result<void, S>;

	ASSERT_CONCEPT    (IsResult, R, void, S);
	ASSERT_NOT_CONCEPT(IsResult, R, int, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, S);
}

TEST("Result", "IsResult Result<int>")
{
	using R = Result<int, S>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, S);
	ASSERT_CONCEPT    (IsResult, R, int, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, double, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, int&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, int&&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&&, S);
}

TEST("Result", "IsResult Result<std::pair>")
{
	using R = Result<std::pair<int, double>, S>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, S);
	ASSERT_NOT_CONCEPT(IsResult, R, int, S);
	ASSERT_CONCEPT    (IsResult, R, std::pair<int, double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, double, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&&, S);
}

TEST("Result", "IsResult Result<std::string>")
{
	using R = Result<std::string, S>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, S);
	ASSERT_NOT_CONCEPT(IsResult, R, int, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, S);
	ASSERT_CONCEPT    (IsResult, R, std::string, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, double, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, std::string&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string&&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&&, S);
}

TEST("Result", "IsResult Result<std::vector>")
{
	using R = Result<std::vector<int>, S>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, S);
	ASSERT_NOT_CONCEPT(IsResult, R, int, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, S);
	ASSERT_CONCEPT    (IsResult, R, std::vector<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, double, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&&, S);
}

TEST("Result", "IsResult Result<std::unique_ptr>")
{
	using R = Result<std::unique_ptr<int>, S>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, S);
	ASSERT_NOT_CONCEPT(IsResult, R, int, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, S);
	ASSERT_CONCEPT    (IsResult, R, std::unique_ptr<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, double, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&&, S);
}

TEST("Result", "IsResult Result<MoveOnlyWrapper>")
{
	using R = Result<MoveOnlyWrapper<int>, S>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, S);
	ASSERT_NOT_CONCEPT(IsResult, R, int, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, S);
	ASSERT_CONCEPT    (IsResult, R, MoveOnlyWrapper<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, double, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&&, S);
}

TEST("Result", "IsResult Result<CopyOnlyWrapper>")
{
	using R = Result<CopyOnlyWrapper<int>, S>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, S);
	ASSERT_NOT_CONCEPT(IsResult, R, int, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, S);
	ASSERT_CONCEPT    (IsResult, R, CopyOnlyWrapper<int>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, double, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, S);

	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&, S);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&&, S);
}
