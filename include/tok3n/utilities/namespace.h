#pragma once

#define BEGIN_NAMESPACE_TOK3N(...) namespace k3::tok3n __VA_OPT__(::) __VA_ARGS__ {
#define END_NAMESPACE_TOK3N(...) }
