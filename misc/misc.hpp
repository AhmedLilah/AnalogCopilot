#pragma once

#include <string>
#include <algorithm>
#include <cctype>

auto trimLeadingAndTraillingSpaces(const std::string& str) -> std::string {
        auto start = std::find_if_not(str.begin(), str.end(), isspace);
        auto end = std::find_if_not(str.rbegin(), str.rend(), isspace).base();
        return (start < end ? std::string(start, end) : std::string());
}

template< typename T>
auto replaceSubStr(std::string & str, std::string oldSubStr, T data) {
        size_t pos = str.find(oldSubStr);
        while(pos != std::string::npos) {
                if constexpr (std::is_same_v<T, char const *>) {
                        str.replace(pos, oldSubStr.size(), data);
                } else if constexpr (std::is_same_v<T, std::string>) {
                        str.replace(pos, oldSubStr.size(), data.c_str());
                } else if constexpr (std::is_convertible_v<T, std::string>) {
                        str.replace(pos, oldSubStr.size(), std::string(data).c_str());
                } else if constexpr (std::is_arithmetic_v<T>) {
                        str.replace(pos, oldSubStr.size(), std::to_string(data).c_str());
                } else {
                        static_assert(std::is_same_v<T, void>, "data can't be converted to string");
                }
                pos = str.find(oldSubStr);
        }
}
