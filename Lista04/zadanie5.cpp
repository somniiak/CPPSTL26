#include <exception>
#include <functional>
#include <stdexcept>
#include <print>
#include <utility>
#include <vector>

int main()
{
    const std::function<int(int, int)> binom =
        [&](int n, int k) {
            if (n < 0 || k < 0)
                throw std::invalid_argument(
                    "n i k muszą być dodatnimi liczbami naturalnymi!");
            if (k > n)
                return 0;
            if (k == 0 || k == n)
                return 1;
            return binom(n - 1, k - 1) + binom(n - 1, k);
        };

    std::vector<std::pair<int, int>> sample = {
        {2, 1}, {4, 2}, {6, 5}, {7, 8}, {9, -1},
    };

    for (const auto& [n, k] : sample)
    {
        try
        {
            std::println("binom({}, {}) = {}", n, k, binom(n, k));
        }
        catch (const std::exception& err)
        {
            std::println("ERROR binom({}, {}): {}", n, k, err.what());
        }
    }

    return 0;
}
