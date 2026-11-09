#include "maximum.hpp"
#include "algorithms.hpp"
#include "array.hpp"
#include "tovar.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

void expect(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error(message);
}

template <typename Exception, typename Function>
void expectThrows(Function action, const std::string& message) {
    try {
        action();
    } catch (const Exception&) {
        return;
    }
    throw std::runtime_error(message);
}

void testMaximum() {
    expect(overloaded::maximum(3, 7) == 7, "int overload");
    expect(overloaded::maximum(7, 3) == 7, "reversed int overload");
    expect(overloaded::maximum(-8, -2) == -2, "negative overload");
    expect(overloaded::maximum(4, 4) == 4, "equal overload");
    expect(overloaded::maximum(2.5, 1.5) == 2.5, "double overload");
    expect(overloaded::maximum(1.5, 2.5) == 2.5, "reversed double overload");
    expect(overloaded::maximum(3, 3.5) == 3.5, "mixed overload");
    expect(overloaded::maximum(3.5, 3) == 3.5, "reversed mixed overload");
    expect(maximum(3, 7) == 7, "int template");
    expect(maximum(7, 3) == 7, "reversed int template");
    expect(maximum(-8, -2) == -2, "negative template");
    expect(maximum(4, 4) == 4, "equal template");
    expect(maximum(2.5, 1.5) == 2.5, "double template");
    expect(maximum(1.5, 2.5) == 2.5, "reversed double template");
    expect(maximum(3, 3.5) == 3.5, "mixed template");
    expect(maximum(3.5, 3) == 3.5, "reversed mixed template");
    expect(maximum(-3, -2.5) == -2.5, "negative mixed template");
    expect(maximum(0.0, 0) == 0.0, "zero template");
    expect(maximum(-1, 2U) == 2U, "signed/unsigned regression");
    expect(maximum(2U, -1) == 2U, "unsigned/signed regression");
    expect(maximum(-1, 0U) == 0U, "negative and unsigned zero");
    expect(maximum(0U, -1) == 0U, "unsigned zero and negative");
    const auto lowest = std::numeric_limits<long long>::min();
    const auto highest = std::numeric_limits<unsigned long long>::max();
    expect(maximum(lowest, highest) == highest, "integer limits");
    expect(maximum(highest, lowest) == highest, "reversed integer limits");
    for (int a = -5; a <= 5; ++a) {
        for (unsigned b = 0; b <= 10; ++b) {
            const long long first = a;
            const long long second = b;
            const auto expected = static_cast<unsigned>(first < second ? second : first);
            expect(maximum(a, b) == expected, "signed/unsigned range");
            expect(maximum(b, a) == expected, "unsigned/signed range");
        }
    }
    static_assert(std::is_same_v<decltype(maximum(3, 7)), int>);
    static_assert(std::is_same_v<decltype(maximum(3, 3.5)), double>);
    static_assert(std::is_same_v<decltype(maximum(-1, 2U)), unsigned int>);
}

void testAlgorithms() {
    const int integers[]{5, -2, 9, 0};
    const double decimals[]{3.5, -1.25, 2.0};
    expect(minimumElement(integers, 4) == -2, "minimum int");
    expect(minimumElement(decimals, 3) == -1.25, "minimum double");
    expect(maximumElement(integers, 4) == 9, "maximum int");
    expect(&minimumElement(integers, 1) == integers, "single element");
    expectThrows<std::invalid_argument>([&] { minimumElement(integers, 0); }, "empty minimum");
    expectThrows<std::invalid_argument>([&] { maximumElement(integers, 0); }, "empty maximum");
    expectThrows<std::invalid_argument>([] { minimumElement<int>(nullptr, 1); }, "null minimum");
    expectThrows<std::invalid_argument>([] { maximumElement<int>(nullptr, 1); }, "null maximum");
    const Tovar items[]{Tovar("Book", 250), Tovar("Pen", 30), Tovar("Notebook", 120)};
    expect(maximumElement(items, 3).getName() == "Book", "maximum Tovar");
    expect(minimumElement(items, 3).getName() == "Pen", "minimum Tovar");
    expect(maximum(items[0], items[1]).getName() == "Book", "two-value Tovar maximum");
    const Tovar ties[]{Tovar("First", 10), Tovar("Second", 10)};
    expect(&maximumElement(ties, 2) == ties, "first maximum on tie");
    expectThrows<std::invalid_argument>([] { Tovar item("Invalid", -1); }, "negative price");
    expectThrows<std::invalid_argument>([] {
        Tovar item("Invalid", std::numeric_limits<double>::quiet_NaN());
    }, "NaN price");
}

struct ThrowOnAssign {
    inline static int alive = 0;
    inline static bool fail = false;
    int value = 0;
    ThrowOnAssign() { ++alive; }
    ThrowOnAssign(const ThrowOnAssign& other) : value(other.value) { ++alive; }
    ~ThrowOnAssign() { --alive; }
    ThrowOnAssign& operator=(const ThrowOnAssign& other) {
        if (fail) throw std::runtime_error("Copy failed");
        value = other.value;
        return *this;
    }
};

void testArray() {
    Array<int> original(3);
    original[0] = 10;
    original[1] = 20;
    original[2] = 30;
    Array<int> copy(original);
    original[0] = 99;
    expect(copy[0] == 10 && &copy[0] != &original[0], "independent copy constructor");
    Array<int> assigned(1);
    assigned = original;
    original[1] = 88;
    expect(assigned.size() == 3 && assigned[1] == 20, "independent copy assignment");
    assigned = assigned;
    expect(assigned[1] == 20, "self assignment");
    const Array<int>& view = copy;
    expect(view[2] == 30, "const access");
    expectThrows<std::out_of_range>([&] { copy[3]; }, "mutable bounds");
    expectThrows<std::out_of_range>([&] { view[3]; }, "const bounds");
    std::ostringstream output;
    copy.output(output);
    expect(output.str() == "10 20 30\n", "array output");
    Array<int> empty;
    Array<int> emptyCopy(empty);
    expect(emptyCopy.size() == 0, "empty copy");
    assigned = empty;
    expect(assigned.size() == 0, "empty assignment");
    expectThrows<std::out_of_range>([&] { empty[0]; }, "empty bounds");
    Array<double> decimals(1);
    decimals[0] = 1.25;
    expect(decimals[0] == 1.25, "Array<double>");
    Array<Tovar> items(1);
    items[0] = Tovar("Book", 250);
    Array<Tovar> itemCopy(items);
    expect(itemCopy[0].getName() == "Book", "Array<Tovar>");
    {
        Array<ThrowOnAssign> source(2);
        Array<ThrowOnAssign> target(1);
        target[0].value = 7;
        ThrowOnAssign::fail = true;
        expectThrows<std::runtime_error>([&] { Array<ThrowOnAssign> failed(source); }, "throwing copy");
        expect(ThrowOnAssign::alive == 3, "failed copy cleanup");
        expectThrows<std::runtime_error>([&] { target = source; }, "throwing assignment");
        expect(ThrowOnAssign::alive == 3 && target.size() == 1 && target[0].value == 7,
               "failed assignment preserves target");
        ThrowOnAssign::fail = false;
    }
    expect(ThrowOnAssign::alive == 0, "destructor cleanup");
}

void testStringSpecialization() {
    const std::string a = "zoo";
    const std::string b = "apple";
    expect(overloaded::maximum(a, b) == "zoo", "lexicographic overload");
    expect(maximum(a, b) == "apple", "longest string specialization");
    expect(maximum(std::string("cat"), std::string("dog")) == "dog", "equal length strings");
    expect(maximum(std::string(), b) == b, "empty string");
}

int main() {
    try {
        testMaximum();
        testAlgorithms();
        testArray();
        testStringSpecialization();
        std::cout << "All tests passed\n";
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
