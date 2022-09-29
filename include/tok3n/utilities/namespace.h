#pragma once

#define TOK3N_BEGIN_NAMESPACE(...) namespace k3::tok3n __VA_OPT__(::) __VA_ARGS__ {
#define TOK3N_END_NAMESPACE(...) }
