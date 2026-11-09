#include "maximum.hpp"
#include "algorithms.hpp"
#include "array.hpp"
#include "tovar.hpp"

#include <iomanip>
#include <iostream>
#include <string>

#ifdef SHOW_TEMPLATE_ERROR
struct WithoutComparison { int value; };
#endif

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Task 1: overloads and template\n";
    std::cout << "Overload int: " << overloaded::maximum(3, 7) << '\n';
    std::cout << "Overload double: " << overloaded::maximum(2.5, 1.5) << '\n';
    std::cout << "Overload mixed: " << overloaded::maximum(3, 3.5) << '\n';
    std::cout << "Template int: " << maximum(3, 7) << '\n';
    std::cout << "Template double: " << maximum(2.5, 1.5) << '\n';
    std::cout << "Template mixed: " << maximum(3, 3.5) << '\n';
    std::cout << "Template signed/unsigned: " << maximum(-1, 2U) << '\n';
    std::cout << "Template unsigned/signed: " << maximum(2U, -1) << '\n';

    std::cout << "\nTask 2: array minimum\n";
    const int integers[]{5, -2, 9, 0};
    const double decimals[]{3.5, -1.25, 2.0};
    std::cout << "Minimum int: " << minimumElement(integers, 4) << '\n';
    std::cout << "Minimum double: " << minimumElement(decimals, 3) << '\n';

    std::cout << "\nTask 3: Tovar comparison\n";
    const Tovar items[]{Tovar("Book", 250), Tovar("Pen", 30), Tovar("Notebook", 120)};
    std::cout << "Most expensive item: " << maximumElement(items, 3) << '\n';

    std::cout << "\nTasks 4 and 5: Array and independent copies\n";
    Array<int> original(3);
    original[0] = 10;
    original[1] = 20;
    original[2] = 30;
    Array<int> copy(original);
    original[0] = 99;
    std::cout << "Original: ";
    original.output();
    std::cout << "Copy: ";
    copy.output();
    Array<int> assigned;
    assigned = original;
    original[1] = 88;
    std::cout << "Assigned copy: ";
    assigned.output();
    Array<double> measurements(2);
    measurements[0] = 1.25;
    measurements[1] = 2.5;
    std::cout << "Array<double>: ";
    measurements.output();

    std::cout << "\nTasks 6 and 7: string specialization and overload\n";
    const std::string a = "zoo";
    const std::string b = "apple";
    std::cout << "Overload, lexicographic: " << overloaded::maximum(a, b) << '\n';
    std::cout << "Specialization, longest string: " << maximum(a, b) << '\n';

    std::cout << "\nTask 8: one algorithm for int and Tovar\n";
    std::cout << "Maximum int: " << maximumElement(integers, 4) << '\n';
    std::cout << "Maximum Tovar: " << maximumElement(items, 3) << '\n';

#ifdef SHOW_TEMPLATE_ERROR
    const WithoutComparison invalid[]{{1}, {2}};
    std::cout << maximumElement(invalid, 2).value << '\n';
#endif
}
