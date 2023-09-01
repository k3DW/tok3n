#include "pch.h"

FIXTURE("Result");

TEST("Result", "IsResult Result<void>")
{
	using R = Result<void>;

	ASSERT_CONCEPT    (IsResult, R, void);
	ASSERT_NOT_CONCEPT(IsResult, R, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>);
}

TEST("Result", "IsResult Result<int>")
{
	using R = Result<int>;

	ASSERT_NOT_CONCEPT(IsResult, R, void);
	ASSERT_CONCEPT    (IsResult, R, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>);

	ASSERT_NOT_CONCEPT(IsResult, R, double);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>);

	ASSERT_NOT_CONCEPT(IsResult, R, int&);
	ASSERT_NOT_CONCEPT(IsResult, R, int&&);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&);
	ASSERT_NOT_CONCEPT(IsResult, R, const int&&);
}

TEST("Result", "IsResult Result<std::pair>")
{
	using R = Result<std::pair<int, double>>;

	ASSERT_NOT_CONCEPT(IsResult, R, void);
	ASSERT_NOT_CONCEPT(IsResult, R, int);
	ASSERT_CONCEPT    (IsResult, R, std::pair<int, double>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>);

	ASSERT_NOT_CONCEPT(IsResult, R, double);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>);

	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>&&);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::pair<int, double>&&);
}

TEST("Result", "IsResult Result<std::string>")
{
	using R = Result<std::string>;

	ASSERT_NOT_CONCEPT(IsResult, R, void);
	ASSERT_NOT_CONCEPT(IsResult, R, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>);
	ASSERT_CONCEPT    (IsResult, R, std::string);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>);

	ASSERT_NOT_CONCEPT(IsResult, R, double);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>);

	ASSERT_NOT_CONCEPT(IsResult, R, std::string&);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string&&);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::string&&);
}

TEST("Result", "IsResult Result<std::vector>")
{
	using R = Result<std::vector<int>>;

	ASSERT_NOT_CONCEPT(IsResult, R, void);
	ASSERT_NOT_CONCEPT(IsResult, R, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string);
	ASSERT_CONCEPT    (IsResult, R, std::vector<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>);

	ASSERT_NOT_CONCEPT(IsResult, R, double);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>);

	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>&&);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::vector<int>&&);
}

TEST("Result", "IsResult Result<std::unique_ptr>")
{
	using R = Result<std::unique_ptr<int>>;

	ASSERT_NOT_CONCEPT(IsResult, R, void);
	ASSERT_NOT_CONCEPT(IsResult, R, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>);
	ASSERT_CONCEPT    (IsResult, R, std::unique_ptr<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>);

	ASSERT_NOT_CONCEPT(IsResult, R, double);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>);

	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>&&);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&);
	ASSERT_NOT_CONCEPT(IsResult, R, const std::unique_ptr<int>&&);
}

TEST("Result", "IsResult Result<MoveOnlyWrapper>")
{
	using R = Result<MoveOnlyWrapper<int>>;

	ASSERT_NOT_CONCEPT(IsResult, R, void);
	ASSERT_NOT_CONCEPT(IsResult, R, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>);
	ASSERT_CONCEPT    (IsResult, R, MoveOnlyWrapper<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>);

	ASSERT_NOT_CONCEPT(IsResult, R, double);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>);

	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>&&);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&);
	ASSERT_NOT_CONCEPT(IsResult, R, const MoveOnlyWrapper<int>&&);
}

TEST("Result", "IsResult Result<CopyOnlyWrapper>")
{
	using R = Result<CopyOnlyWrapper<int>>;

	ASSERT_NOT_CONCEPT(IsResult, R, void);
	ASSERT_NOT_CONCEPT(IsResult, R, int);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<int, double>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::string);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<int>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<int>);
	ASSERT_CONCEPT    (IsResult, R, CopyOnlyWrapper<int>);

	ASSERT_NOT_CONCEPT(IsResult, R, double);
	ASSERT_NOT_CONCEPT(IsResult, R, std::pair<double, int>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::wstring);
	ASSERT_NOT_CONCEPT(IsResult, R, std::vector<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, std::unique_ptr<long>);
	ASSERT_NOT_CONCEPT(IsResult, R, MoveOnlyWrapper<double>);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<double>);

	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&);
	ASSERT_NOT_CONCEPT(IsResult, R, CopyOnlyWrapper<int>&&);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&);
	ASSERT_NOT_CONCEPT(IsResult, R, const CopyOnlyWrapper<int>&&);
}
