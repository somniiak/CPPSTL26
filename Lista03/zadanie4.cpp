#include <print>
#include <stdexcept>
#include <type_traits>
#include <utility>

template <typename A, typename B>
void moveValueImpl(A src, B& dst, std::true_type)
{
    dst = std::move(*src);
}

template <typename A, typename B>
void moveValueImpl(A src, B& dst, std::false_type)
{
    dst = std::move(src);
}

template <typename A, typename B>
void moveValue(A src, B& dst)
{
    if (!std::is_convertible<std::remove_pointer_t<A>, B>())
        throw std::runtime_error(
            "Nie można przekonwertować obiektu do danego typu!");

    moveValueImpl(src, dst, std::is_pointer<A>());
}

int main()
{
    int x = 67213769;
    int* y = &x;
    double z = 0.001;

    std::println("x = {}, y = {}, z = {}", x, *y, z);
    moveValue(y, z);
    std::println("x = {}, y = {}, z = {}", x, *y, z);

    return 0;
}