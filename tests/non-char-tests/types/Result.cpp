#include "samples.h"

FIXTURE("result");

TEST("result", "result_of result<void>")
{
	using R = detail::result<void, value_type>;

	ASSERT_CONCEPT    (detail::result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<int>, value_type);
}

TEST("result", "result_of result<int>")
{
	using R = detail::result<int, value_type>;

	ASSERT_NOT_CONCEPT(detail::result_of, R, void, value_type);
	ASSERT_CONCEPT    (detail::result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, int&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, int&&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const int&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const int&&, value_type);
}

TEST("result", "result_of result<std::pair>")
{
	using R = detail::result<std::pair<int, double>, value_type>;

	ASSERT_NOT_CONCEPT(detail::result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, int, value_type);
	ASSERT_CONCEPT    (detail::result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<int, double>&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<int, double>&&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const std::pair<int, double>&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const std::pair<int, double>&&, value_type);
}

TEST("result", "result_of result<std::string>")
{
	using R = detail::result<std::string, value_type>;

	ASSERT_NOT_CONCEPT(detail::result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<int, double>, value_type);
	ASSERT_CONCEPT    (detail::result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, std::string&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::string&&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const std::string&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const std::string&&, value_type);
}

TEST("result", "result_of result<std::vector>")
{
	using R = detail::result<std::vector<int>, value_type>;

	ASSERT_NOT_CONCEPT(detail::result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::string, value_type);
	ASSERT_CONCEPT    (detail::result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<int>&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<int>&&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const std::vector<int>&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const std::vector<int>&&, value_type);
}

TEST("result", "result_of result<std::unique_ptr>")
{
	using R = detail::result<std::unique_ptr<int>, value_type>;

	ASSERT_NOT_CONCEPT(detail::result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<int>, value_type);
	ASSERT_CONCEPT    (detail::result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<int>&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<int>&&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const std::unique_ptr<int>&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const std::unique_ptr<int>&&, value_type);
}

TEST("result", "result_of result<MoveOnlyWrapper>")
{
	using R = detail::result<MoveOnlyWrapper<int>, value_type>;

	ASSERT_NOT_CONCEPT(detail::result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_CONCEPT    (detail::result_of, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<int>&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<int>&&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const MoveOnlyWrapper<int>&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const MoveOnlyWrapper<int>&&, value_type);
}

TEST("result", "result_of result<CopyOnlyWrapper>")
{
	using R = detail::result<CopyOnlyWrapper<int>, value_type>;

	ASSERT_NOT_CONCEPT(detail::result_of, R, void, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, int, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<int, double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::string, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<int>, value_type);
	ASSERT_CONCEPT    (detail::result_of, R, CopyOnlyWrapper<int>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, double, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::pair<double, int>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::wstring, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::vector<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, std::unique_ptr<long>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, MoveOnlyWrapper<double>, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<double>, value_type);

	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<int>&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, CopyOnlyWrapper<int>&&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const CopyOnlyWrapper<int>&, value_type);
	ASSERT_NOT_CONCEPT(detail::result_of, R, const CopyOnlyWrapper<int>&&, value_type);
}
