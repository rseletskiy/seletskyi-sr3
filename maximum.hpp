#pragma once

#include <type_traits>

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

}

template <typename T, typename U>
std::common_type_t<T, U> maximum(T a, U b) {
    using Result = std::common_type_t<T, U>;
    const Result first = a;
    const Result second = b;
    return first < second ? second : first;
}
