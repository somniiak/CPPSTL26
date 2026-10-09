#include <iostream>
#include <string>

void printDate(int day, std::string month, int year) {
    std::cout << day << " " << month << " " << year << "\n";
}

int main(int argc, char** argv)
{
    if (argc != 4) {
        std::cout << "Niepoprawny format! Podaj date w postaci:\n";
        std::cout << "DZIEŃ MIESIĄĆ ROK";
        return 0;
    }

    int day = std::stoi(argv[1]);
    int year = std::stoi(argv[3]);

    if (day < 1 || day > 31) {
        std::cout << "Miesiąc nie może mieć ponad 31 dni!\n";
        return 0;
    }

    switch(int month = std::stoi(argv[2])) {
        case 1:
            printDate(day, "stycznia", year);
            break;
        case 2:
            printDate(day, "lutego", year);
            break;
        case 3:
            printDate(day, "marca", year);
            break;
        case 4:
            printDate(day, "kwietnia", year);
            break;
        case 5:
            printDate(day, "maja", year);
            break;
        case 6:
            printDate(day, "czerwca", year);
            break;
        case 7:
            printDate(day, "lipca", year);
            break;
        case 8:
            printDate(day, "sierpnia", year);
            break;
        case 9:
            printDate(day, "września", year);
            break;
        case 10:
            printDate(day, "października", year);
            break;
        case 11:
            printDate(day, "listopada", year);
            break;
        case 12:
            printDate(day, "grudnia", year);
            break;
        default:
            std::cout << "Niepoprawny miesiąc!\n";
    }

    return 0;
}
