#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iterator>
#include <print>
#include <stdexcept>
#include <string>

int main(int argc, char** argv)
{
    if (argc < 2)
        throw std::invalid_argument("Nie podano nazwy pliku!");

    std::ifstream file(argv[1]);

    if (!file.is_open())
        throw std::runtime_error("Nie można otworzyć pliku!");

    // Trzeba zainicjować, żeby wyzerować
    std::array<int, 26> count = {};
    int letters = 0;

    std::istream_iterator<char> fileBeg(file), fileEnd;

    std::for_each(fileBeg, fileEnd, [&](char c) {
        if (std::isalpha(c)) {
            ++count[std::tolower(static_cast<char>(c)) - 'a'];
            ++letters;
        }
    });

    for (char c = 'a'; c < 'z'; c++)
    {
        double occurences = count[c - 'a'];
        double percent = (occurences / letters) * 100;
        std::string bar = std::string(
            static_cast<int>(std::round(percent)), '#');

        std::println("{}: {}\t| {:6.2f}% | {}", c, occurences, percent, bar);
    }

    return 0;
}
