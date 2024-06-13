#include "pch.h"
#include "char-tests/samples.h"

FIXTURE("Result");

TEST("Result", "IsResult Result<void>")
{
	using R = Result<void, char>;

	ASSERT_CONCEPT    (IsResult, R, void, char);
	ASSERT_NOT_CONCEPT(IsResult, R, int, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, char);
}

TEST("Result", "IsResult Result<int>")
{
	using R = Result<int, char>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, char);
	ASSERT_CONCEPT    (IsResult, R, int, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, double, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, int&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, int&&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&&, char);
}

TEST("Result", "IsResult Result<std::pair>")
{
	using R = Result<std::pair<int, double>, char>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, char);
	ASSERT_NOT_CONCEPT(IsResult, R, int, char);
	ASSERT_CONCEPT    (IsResult, R, std::pair<int, double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, double, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&&, char);
}

TEST("Result", "IsResult Result<std::string>")
{
	using R = Result<std::string, char>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, char);
	ASSERT_NOT_CONCEPT(IsResult, R, int, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, char);
	ASSERT_CONCEPT    (IsResult, R, std::string, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, double, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, std::string&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string&&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&&, char);
}

TEST("Result", "IsResult Result<std::vector>")
{
	using R = Result<std::vector<int>, char>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, char);
	ASSERT_NOT_CONCEPT(IsResult, R, int, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, char);
	ASSERT_CONCEPT    (IsResult, R, std::vector<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, double, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&&, char);
}

TEST("Result", "IsResult Result<std::unique_ptr>")
{
	using R = Result<std::unique_ptr<int>, char>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, char);
	ASSERT_NOT_CONCEPT(IsResult, R, int, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, char);
	ASSERT_CONCEPT    (IsResult, R, std::unique_ptr<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, double, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&&, char);
}

TEST("Result", "IsResult Result<MoveOnlyWrapper>")
{
	using R = Result<MoveOnlyWrapper<int>, char>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, char);
	ASSERT_NOT_CONCEPT(IsResult, R, int, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, char);
	ASSERT_CONCEPT    (IsResult, R, MoveOnlyWrapper<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, double, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&&, char);
}

TEST("Result", "IsResult Result<CopyOnlyWrapper>")
{
	using R = Result<CopyOnlyWrapper<int>, char>;

	ASSERT_NOT_CONCEPT(IsResult, R, void, char);
	ASSERT_NOT_CONCEPT(IsResult, R, int, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>, char);
	ASSERT_CONCEPT    (IsResult, R, CopyOnlyWrapper<int>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, double, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>, char);

	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&, char);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&&, char);
}
