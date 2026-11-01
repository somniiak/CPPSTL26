#include <algorithm>
#include <print>
#include <vector>
#include <string>

// https://moderncppdocumentation.com/functions/composing-functions/

template <typename F, typename G>
class Compose
{
    private:
        F f; G g;

    public:
        Compose(F f_, G g_) : f(std::move(f_)), g(std::move(g_)) {}

        template <typename T>
        auto operator()(const T& arg) const { return f(g(arg)); }
};

int square(int n) { return n * n; }

int increment(int n) { return n + 1; }

int stoi(std::string str) { return std::stoi(str); }

int main()
{
    std::vector<std::string> input = {"1", "2", "3", "4", "5"};
    std::vector<int> result(input.size());

    std::transform(input.cbegin(), input.cend(), result.begin(),
        Compose(increment, Compose(square, stoi)));

    std::println("{}", input);
    std::println("{}", result);

    return 0;
}
