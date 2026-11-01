#include <algorithm>
#include <cctype>
#include <string>
#include <print>

// Wskaźniki do funkcji
// https://www.ibm.com/docs/en/xl-c-and-cpp-aix/16.1.0?topic=functions-pointers

template<typename T>
using fun = T (*)(T);

template<typename T>
void transf(T tab[], int n, fun<T> f)
{
    for (int i = 0; i < n; ++i)
        tab[i] = f(tab[i]);
}

int square(int x)
{
    return x * x;
}

// https://stackoverflow.com/a/735215
std::string uppercase(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

int main()
{
    int nums[] = {1, 2, 3, 4, 5};
    const int s1 = sizeof(nums) / sizeof(nums[0]);

    std::println("{}", nums);
    transf<int>(nums, s1, square);
    std::println("{}", nums);

    std::string strs[] = {"abc", "def", "ghi", "jkl"};
    const int s2 = sizeof(strs) / sizeof(strs[0]);

    std::println("{}", strs);
    transf<std::string>(strs, s2, uppercase);
    std::println("{}", strs);

    return 0;
}
