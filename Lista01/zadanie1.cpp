#include <iostream>

int main()
{
    std::cout << R"(Instyut Informatyki Uniwersyetu Wrocławskiego
ul. Joliot-Curie 15
50-383 Wrocław
)";

    std::cout << "\n" << R"(C:\Users\Default\Documents\TextFiles)" << "\n";

// https://stackoverflow.com/a/56710099
// Ogranicznik jest zwykle pomijany (same nawiasy)
// ale można do niego użyć dowolnych znaków.

    std::cout << "\n" << R"delimiter(("")()"")"()"''()")delimiter" << "\n";

    return 0;
}