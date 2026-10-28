#include "maximum.hpp"

#include <iostream>
#include <stdexcept>
#include <type_traits>

void expect(bool condition) {
    if (!condition) throw std::runtime_error("Test failed");
}

int main() {
    try {
        expect(overloaded::maximum(3, 7) == 7);
        expect(overloaded::maximum(7, 3) == 7);
        expect(overloaded::maximum(-8, -2) == -2);
        expect(overloaded::maximum(4, 4) == 4);
        expect(overloaded::maximum(2.5, 1.5) == 2.5);
        expect(overloaded::maximum(1.5, 2.5) == 2.5);
        expect(overloaded::maximum(3, 3.5) == 3.5);
        expect(overloaded::maximum(3.5, 3) == 3.5);
        expect(maximum(3, 7) == 7);
        expect(maximum(7, 3) == 7);
        expect(maximum(-8, -2) == -2);
        expect(maximum(4, 4) == 4);
        expect(maximum(2.5, 1.5) == 2.5);
        expect(maximum(1.5, 2.5) == 2.5);
        expect(maximum(3, 3.5) == 3.5);
        expect(maximum(3.5, 3) == 3.5);
        expect(maximum(-3, -2.5) == -2.5);
        expect(maximum(0.0, 0) == 0.0);
        static_assert(std::is_same_v<decltype(maximum(3, 7)), int>);
        static_assert(std::is_same_v<decltype(maximum(3, 3.5)), double>);
        std::cout << "All tests passed\n";
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
