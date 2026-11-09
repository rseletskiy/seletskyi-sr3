#pragma once

#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename T>
class Array {
private:
    std::size_t size_;
    T* data_;

public:
    explicit Array(std::size_t size = 0);
    Array(const Array& other);
    ~Array();
    Array& operator=(const Array& other);
    void swap(Array& other) noexcept;
    std::size_t size() const noexcept;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    void output(std::ostream& stream = std::cout) const;
};

template <typename T>
Array<T>::Array(std::size_t size)
    : size_(size), data_(size == 0 ? nullptr : new T[size]{}) {}

template <typename T>
Array<T>::Array(const Array& other) : size_(other.size_), data_(nullptr) {
    std::unique_ptr<T[]> copy(size_ == 0 ? nullptr : new T[size_]{});
    for (std::size_t i = 0; i < size_; ++i) copy[i] = other.data_[i];
    data_ = copy.release();
}

template <typename T>
Array<T>::~Array() {
    delete[] data_;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        Array copy(other);
        swap(copy);
    }
    return *this;
}

template <typename T>
void Array<T>::swap(Array& other) noexcept {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

template <typename T>
std::size_t Array<T>::size() const noexcept {
    return size_;
}

template <typename T>
T& Array<T>::operator[](std::size_t index) {
    if (index >= size_) throw std::out_of_range("Array index out of range");
    return data_[index];
}

template <typename T>
const T& Array<T>::operator[](std::size_t index) const {
    if (index >= size_) throw std::out_of_range("Array index out of range");
    return data_[index];
}

template <typename T>
void Array<T>::output(std::ostream& stream) const {
    for (std::size_t i = 0; i < size_; ++i) {
        if (i != 0) stream << ' ';
        stream << data_[i];
    }
    stream << '\n';
}
