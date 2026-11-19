#include <algorithm>
#include <print>
#include <string>
#include <vector>

// https://en.cppreference.com/cpp/algorithm/next_permutation
// https://stackoverflow.com/a/1995356
// `input` musi być posortowany, bo `next_permutation` zwraca,
// leksykograficznie następną permutację.

std::vector<std::string> permutate(std::string input)
{
    std::sort(input.begin(), input.end());
    std::vector<std::string> result = { input };

    while (std::next_permutation(input.begin(), input.end()))
        result.push_back(input);

    return result;
}

int main(int argc, char** argv)
{
    std::string input = argc < 2 ? "example" : argv[1];

    for (std::string perm : permutate(input))
        std::println("{}", perm);

    return 0;
}
