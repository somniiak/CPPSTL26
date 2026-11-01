#include <utility>
#include <print>

template <typename F, typename G>
class Sequence
{
    private:
        F f; G g;

    public:
        Sequence(F f_, G g_) : f(std::move(f_)), g(std::move(g_)) {}

        template <typename T>
        auto operator()(const T& arg) const { f(arg); return g(arg); }
};

int square(int n) { return n * n; }

int increment(int n) { return n + 1; }

int main()
{
    int x = 1;
    std::println("x = {}", x);

    int y = Sequence(square, increment)(x);
    std::println("Sequence(square, increment)(x): {}", y);

    int z = Sequence(Sequence(increment, increment), square)(x);
    std::println("Sequence(Sequence(increment, increment), square)(x): {}", z);

    return 0;
}
