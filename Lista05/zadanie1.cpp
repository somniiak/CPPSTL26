#include "lexer.hpp"
#include <vector>
#include <string>
#include <print>

int main()
{
    std::vector<std::string> tests = {
        "<=>=",
        "x %= [2.3 * (5 + 1)]",
        "val = 0.67 > 3",
    };

    for (std::string test : tests)
    {
        std::println("{}:", test);
        std::println("{}", Lexer::tokenize(test));
        std::println();
    }
}
