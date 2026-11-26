#include <algorithm>
#include <array>
#include <cmath>
#include <complex>
#include <format>
#include <fstream>
#include <stdexcept>
#include <utility>

std::complex<double> zeta(std::complex<double> z, int times)
{
    std::complex<double> result = 0;

    for (int i = 1; i <= times; i++)
        result += std::pow(i, -z);

    return result;
}

std::complex<double> alt_zeta(std::complex<double> z, int times)
{
    if (z.real() <= 0 || z.real() >= 1)
        throw std::invalid_argument("alt_zeta przyjmuje z częścią rzeczywistą 0 < Re(z) < 1!");

    std::complex<double> result = 0;

    for (int i = 1; i <= times; i++)
        result += std::pow(-1, i + 1) * std::pow(i, -z);

    return result * (1.0 / (1.0 - std::pow(2, 1.0 - z)));
}

int main()
{
    // Tablica (Re: 0.5, Im: -30, ..., 30)
    std::array<std::pair<double, std::complex<double>>, 1201> table;

    std::generate(table.begin(), table.end(), [i = 0]() mutable {
        double t = (i++ - 600) / 20.0;
        return std::make_pair(t, alt_zeta({0.5, t}, 1000));
    });

    std::ofstream file("zadanie2.csv");

    if (!file.is_open())
        throw std::runtime_error("Nie można otworzyć pliku!");

    file << "z,re,im\n";
    for (const auto& [t, val] : table)
        file << std::format("{:.2f},{:.10f},{:.10f}\n", t, val.real(), val.imag());

    return 0;
}
