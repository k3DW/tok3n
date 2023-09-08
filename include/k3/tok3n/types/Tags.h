#pragma once

namespace k3::tok3n {

constexpr struct FailureTag final {} failure;
constexpr struct SuccessTag final {} success;

struct InputSpanTag final {};
struct OutputSpanTag final {};

} // namespace k3::tok3n
