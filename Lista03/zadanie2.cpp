#include <iomanip>
#include <iostream>
#include <limits>

// Prezycja wyników w std::cout
// https://en.cppreference.com/cpp/io/manip/setprecision

int main()
{
    const auto default_precision = std::cout.precision();
    const auto max_precision = std::numeric_limits<long double>::digits10 + 1;

    std::cout << "default_precision: " << default_precision << "\n";
    std::cout << "max_precision: " << max_precision << "\n";

    std::cout << std::setprecision(max_precision)
        << "denorm_min(long double): "
        << std::numeric_limits<long double>::denorm_min() << "\n"
        << "max(long double): "
        << std::numeric_limits<long double>::max() << "\n"
        << "has_infinity(long double): "
        << std::numeric_limits<long double>::has_infinity << "\n"
        << "epsilon(long double): "
        << std::numeric_limits<long double>::epsilon() << "\n";

    return 0;
}