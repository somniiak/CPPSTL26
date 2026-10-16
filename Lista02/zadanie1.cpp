#include <algorithm>
#include <random>
#include <iostream>
#include <memory>
#include <vector>

class Counter
{
    private:
        std::uint64_t value = 1;

    public:
        Counter() = default;

        virtual ~Counter() {
            std::cerr << "~Counter: " << value << "\n";
        }

        void incValue(int k) {
            value += k;
        }

        std::uint64_t getValue() {
            return value;
        }
};

void random_incrementer(std::unique_ptr<Counter[]> counters, int size, int time, int times)
{
    if (time > times)
        return;

    std::mt19937 mt{std::random_device{}()};

    std::vector<int> indices(size / 10);
    std::generate(
        indices.begin(), indices.end(),
        [&](){ return mt() % size; }
    );

    for (int index : indices)
        counters[index].incValue(time);

    random_incrementer(std::move(counters), size, time + 1, times);
}

int main()
{
    const int n = 10;
    const int m = 10;

    std::unique_ptr<Counter[]> counters = std::make_unique<Counter[]>(n);
    random_incrementer(std::move(counters), n, 1, m);

    return 0;
}