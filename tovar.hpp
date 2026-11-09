#pragma once

#include <cmath>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>

class Tovar {
private:
    std::string name;
    double price = 0;

public:
    Tovar() = default;

    Tovar(std::string name, double price)
        : name(std::move(name)), price(price) {
        if (!std::isfinite(price) || price < 0) {
            throw std::invalid_argument("Price must be finite and nonnegative");
        }
    }

    const std::string& getName() const { return name; }
    double getPrice() const { return price; }

    bool operator<(const Tovar& other) const {
        return price < other.price;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Tovar& item) {
        return stream << item.name << " (" << item.price << " UAH)";
    }
};
