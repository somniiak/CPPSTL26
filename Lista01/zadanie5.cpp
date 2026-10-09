#include <cmath>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 4) {
        std::cout << "Podaj trzy współczynniki równania kwadratowego (a, b, c)!\n";
        return 0;
    }

    float a = std::stof(argv[1]);
    float b = std::stof(argv[2]);
    float c = std::stof(argv[3]); 

    if (a == 0) {
        std::cout << "To nie jest równanie kwadratowe (a = 0)!\n";
    } else if (double delta = b * b - 4 * a * c; delta > 0) {
        double x1 = (-b - sqrt(delta)) / (2 * a);
        double x2 = (-b + sqrt(delta)) / (2 * a);
        std::cout << "x1 = " << x1 << "\n";
        std::cout << "x2 = " << x2 << "\n";
    } else if (delta == 0) {
        double x0 = -b / (2 * a);
        std::cout << "x0 = " << x0 << "\n";
    } else {
        std::cout << "Brak rzeczywtistych miejsc zerowych.\n";
    }

    return 0;
}