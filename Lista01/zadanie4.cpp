#include <cstdint>
#include <iostream>

auto lucas(std::uint64_t n) {
    if (n == 0)
        return 2;
    else if (n == 1)
        return 1;
    return lucas(n - 1) + lucas(n - 2);
}

int main(int argc, char** argv)
{
    if (argc == 1)
        std::cout << "Podaj liczbę!\n";
    else
        std::cout << lucas(std::stoull(argv[1])) << "\n";

    return 0;
}