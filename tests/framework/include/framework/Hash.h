#pragma once
#include <bit>
#include <string_view>

constexpr std::size_t test_hash(std::string_view s)
{
    std::size_t hash = 0;
    for (char c : s)
    {
        hash = std::rotl(hash, 1) + c;
    }
    return hash;
}

constexpr std::size_t test_hash(std::string_view s1, std::string_view s2)
{
    return test_hash(s1) ^ test_hash(s2);
}
