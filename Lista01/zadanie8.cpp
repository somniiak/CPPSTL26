#include <iostream>
#include <vector>
#include <iterator>

// https://stackoverflow.com/a/10935920

using constIter = std::vector<int>::const_iterator;

constIter lower_bound(const std::vector<int>& data, int value) {
    auto [left, right] = std::pair{data.begin(), data.end()};

    while (left < right) {
        auto middle = left + (right - left) / 2;

        if ((*middle <=> value) < 0)
            left = middle + 1;
        else
            right = middle;
    }

    return left;
}

constIter upper_bound(const std::vector<int>& data, int value) {
    auto [left, right] = std::pair{data.begin(), data.end()};

    while (left < right) {
        auto middle = left + (right - left) / 2;

        if ((*middle <=> value) <= 0)
            left = middle + 1;
        else
            right = middle;
    }

    return left;
}

std::pair<constIter, constIter> findRange(const std::vector<int>& data, int value) {
    auto first = lower_bound(data, value);
    auto past = upper_bound(data, value);

    // Szukanej wartości nie ma w wektorze
    if (first == past)
        return {data.end(), data.end()};

    return {first, std::prev(past)};
}

int main()
{
    std::vector<int> numbers = {
        1, 2, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7, 7, 8, 9
    };

    auto [first, last] = findRange(numbers, 5);

    if (first == numbers.cend())
        std::cout << "Brak szukanej wartości!\n";
    else {
        std::cout << "[idx " << std::distance(numbers.cbegin(), first) << "]: val " << *first << ", ";
        std::cout << "[idx " << std::distance(numbers.cbegin(), last) << "]: val " << *last << "\n";
    }

    return 0;
}