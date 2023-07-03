#pragma once
#include "TestResult.h"

class Fixture;

class FixtureResult
{
public:	
	FixtureResult(const Fixture* fixture)
		: _fixture(fixture)
	{}

	void add_success(TestResult&& result) { _succeeded.push_back(std::move(result)); }
	void add_failure(TestResult&& result) { _failed.push_back(std::move(result)); }

	bool has_errors() const { return not _failed.empty(); }

	const Fixture* fixture() const { return _fixture; }
	const auto& succeeded()  const { return _succeeded; }
	const auto& failed()     const { return _failed; }

private:
	const Fixture* _fixture;
	std::vector<TestResult> _succeeded;
	std::vector<TestResult> _failed;
};

class FixtureResults
{
public:
	void add_success(FixtureResult&& result) { _succeeded.push_back(std::move(result)); }
	void add_failure(FixtureResult&& result) { _failed.push_back(std::move(result)); }

	bool has_errors() const { return not _failed.empty(); }

	const auto& succeeded() const { return _succeeded; }
	const auto& failed()    const { return _failed; }

private:
	std::vector<FixtureResult> _succeeded;
	std::vector<FixtureResult> _failed;
};
