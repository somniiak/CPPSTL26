#include <ratio>
#include <print>

template <int Cur, int Max, typename Prev>
void harmonic()
{
    using Next = std::ratio_add<Prev, std::ratio<1, Cur>>::type;

    std::println("H_{} = {} / {}", Cur, Next::num, Next::den);

    if constexpr (Cur < Max)
        harmonic<Cur + 1, Max, Next>();
}

int main()
{
    harmonic<1, 46, std::ratio<0, 1>>();
}