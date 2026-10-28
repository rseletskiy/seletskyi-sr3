#include "maximum.hpp"

#include <iostream>

int main() {
    std::cout << "Overload int: " << overloaded::maximum(3, 7) << '\n'
              << "Overload double: " << overloaded::maximum(2.5, 1.5) << '\n'
              << "Overload mixed: " << overloaded::maximum(3, 3.5) << '\n'
              << "Template int: " << maximum(3, 7) << '\n'
              << "Template double: " << maximum(2.5, 1.5) << '\n'
              << "Template mixed: " << maximum(3, 3.5) << '\n';
}
