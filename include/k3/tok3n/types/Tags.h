#pragma once

namespace k3::tok3n {

inline constexpr struct FailureTag final {} failure;
inline constexpr struct SuccessTag final {} success;

struct InputSpanTag final {};
struct OutputSpanTag final {};

} // namespace k3::tok3n
