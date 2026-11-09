#pragma once

#include <type_traits>
#include <string>

namespace overloaded {

inline int maximum(int a, int b) {
    return a < b ? b : a;
}

inline double maximum(double a, double b) {
    return a < b ? b : a;
}

inline double maximum(int a, double b) {
    return a < b ? b : a;
}

inline double maximum(double a, int b) {
    return a < b ? b : a;
}

inline std::string maximum(const std::string& a, const std::string& b) {
    return a < b ? b : a;
}

}

template <typename T, typename U>
std::common_type_t<T, U> maximum(T a, U b) {
    using Result = std::common_type_t<T, U>;
    if constexpr (std::is_integral_v<T> && std::is_integral_v<U>
                  && (std::is_signed_v<T> != std::is_signed_v<U>)) {
        if constexpr (std::is_signed_v<T>) {
            if (a < 0) return static_cast<Result>(b);
            using UnsignedT = std::make_unsigned_t<T>;
            return static_cast<UnsignedT>(a) < b
                ? static_cast<Result>(b) : static_cast<Result>(a);
        } else {
            if (b < 0) return static_cast<Result>(a);
            using UnsignedU = std::make_unsigned_t<U>;
            return a < static_cast<UnsignedU>(b)
                ? static_cast<Result>(b) : static_cast<Result>(a);
        }
    } else {
        const Result first = a;
        const Result second = b;
        return first < second ? second : first;
    }
}

template <>
inline std::string maximum<std::string, std::string>(std::string a, std::string b) {
    if (a.size() != b.size()) return a.size() < b.size() ? b : a;
    return a < b ? b : a;
}

