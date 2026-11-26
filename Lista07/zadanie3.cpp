#include <array>
#include <cstddef>
#include <format>
#include <fstream>
#include <random>
#include <stdexcept>
#include <string>

const std::array<double, 26> letterFreq = {
  8.37, 1.93, 3.89, 3.35, 8.68, 0.26, 1.46, 1.25, 8.83, 2.28,
  3.01, 2.24, 2.81, 5.69, 7.53, 2.87, 0.00, 4.15, 4.13, 3.85,
  2.06, 0.00, 4.11, 0.00, 4.03, 5.33
};

int main(int argc, char** argv)
{
    if (argc != 3)
        throw std::runtime_error("Podaj nazwę pliku i długość tekstu!");

    if (std::stoi(argv[2]) <= 0)
        throw std::format_error("Długość tekstu musi być dodatnia!");

    const std::string fileName = argv[1];
    std::size_t textLength = std::stoul(argv[2]);

    std::ofstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("Nie można otworzyć pliku!");

    std::random_device rd;
    std::mt19937 gen(rd());

    // https://cplusplus.com/reference/random/binomial_distribution/binomial_distribution/
    // Rozkład dwumianowy (t, p): zakres [0, t], ppb. sukcesu `p`
    std::discrete_distribution<int> rndLetter(letterFreq.begin(), letterFreq.end());
    std::binomial_distribution<int> rndLength(11, 0.4);

    std::string text;

    while (text.length() < textLength)
    {
        if (!text.empty())
            text += " ";

        int len = rndLength(gen) + 1;

        for (int i = 0; i < len && text.length() < textLength; i++)
            text += static_cast<char>('a' + rndLetter(gen));
    }

    // Zapis tekstu do pliku
    file << text;

    return 0;
}
