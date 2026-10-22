#include <iostream>
#include <limits>

int main()
{
    std::cout << "min(long long int): "
        << std::numeric_limits<long long int>::min() << "\n";

    std::cout << "max(long long int): "
        << std::numeric_limits<long long int>::max() << "\n";

    std::cout << "is_signed(long long int): "
        << std::numeric_limits<long long int>::is_signed << "\n";

    std::cout << "digits(long long int): "
        << std::numeric_limits<long long int>::digits << "\n";

    std::cout << "digits10(long long int): "
        << std::numeric_limits<long long int>::digits10 << "\n";

    return 0;
}