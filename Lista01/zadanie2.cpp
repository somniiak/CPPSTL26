#include <iostream>
#include <set>

// 1 sposób
// typedef std::set<std::string> StrSet;

// 2 sposób
using StrSet = std::set<std::string>;

int main()
{
    StrSet words = {
        "hello", "world", "logika", "polityka",
            "kangur", "książka", "futro", "szkoła"
    };

    for (const auto& word : words)
        std::cout << word << std::endl;

    return 0;
}