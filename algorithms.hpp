#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
const T& minimumElement(const T* values, std::size_t size) {
    if (values == nullptr || size == 0) {
        throw std::invalid_argument("Array must contain at least one element");
    }
    const T* result = values;
    for (std::size_t i = 1; i < size; ++i) {
        if (values[i] < *result) result = values + i;
    }
    return *result;
}

template <typename T>
const T& maximumElement(const T* values, std::size_t size) {
    if (values == nullptr || size == 0) {
        throw std::invalid_argument("Array must contain at least one element");
    }
    const T* result = values;
    for (std::size_t i = 1; i < size; ++i) {
        if (*result < values[i]) result = values + i;
    }
    return *result;
}
