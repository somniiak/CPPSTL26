#include <array>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <limits>
#include <print>
#include <random>

template<typename T, std::size_t N, typename Dist>
void fillRandom(std::array<std::array<T, N>, N>& A, std::mt19937& gen, Dist& dist)
{
    for (std::size_t i = 0; i < N; i++)
    {
        for (std::size_t j = 0; j < N; j++)
        {
            A[i][j] = dist(gen);
        }
    }
}

template<typename T, std::size_t N>
void squareMatrix(std::array<std::array<T, N>, N>& A)
{
    std::array<std::array<T, N>, N> squared = {};

    for (std::size_t i = 0; i < N; i++)
    {
        for (std::size_t j = 0; j < N; j++)
        {
            const T aij = A[i][j];

            for (std::size_t k = 0; k < N; k++)
                squared[i][j] += aij * A[i][k];
        }
    }

    A = squared;
}

template<typename T, std::size_t N>
void measureTime(const char* name, std::array<std::array<T, N>, N>& arr, int repeats)
{
    using clock = std::chrono::high_resolution_clock;

    const auto start = clock::now();

    for (int i = 0; i < repeats; i++)
        squareMatrix(arr);

    const auto end = clock::now();

    const std::chrono::duration<double, std::milli> total = end - start;

    const double total_ms = total.count();
    const int total_int = static_cast<int>(total_ms);
    const double total_min = total_ms / 1000.0 / 60.0;

    const double average_ms = total.count() / repeats;
    const int average_int = static_cast<int>(average_ms);
    const double average_min = average_ms / 1000.0 / 60.0;

    std::println("{}:", name);
    std::println("  - {} powtórzeń", repeats);
    std::println("  - średnio: {}ms", average_int);
    std::println("  - średnio: {:.3f}min ", average_min);
    std::println("  - w sumie: {}ms", total_int);
    std::println("  - w sumie: {:.3f}min ", total_min);
}

int main()
{
    std::mt19937 gen(std::random_device{}());

    // std::uniform_real_distribution zwraca liczby z przedziału otwartego [a, b)
    // więc dodajemy najbliższą liczbę większą od b (jakiś epsilon), żeby dostać
    // przedział domknięty z obu stron [a, b].

    const float a = 0.5, b = 2.0;
    std::uniform_real_distribution<float> dist(
        a, std::nextafter(b, std::numeric_limits<float>::max()));

    std::array<std::array<float, 50>, 50> small = {};
    std::array<std::array<float, 100>, 100> medium = {};
    std::array<std::array<float, 200>, 200> large = {};

    fillRandom(small, gen, dist);
    fillRandom(medium, gen, dist);
    fillRandom(large, gen, dist);

    measureTime("small", small, 1000);
    measureTime("medium", medium, 500);
    measureTime("large", large, 100);

    return 0;
}
