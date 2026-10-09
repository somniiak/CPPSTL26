#include <cstdint>
#include <iostream>

enum class Name: std::uint16_t {
    Jan, Paweł, Karol, Aleksander,
    Monika, Magda, Magdalena, Beata,
};

void greetName(const std::string& message, Name name) {
    switch (name) {
        case Name::Jan:
            std::cout << message << " Jan.\n";
            break;
        
        case Name::Paweł:
            std::cout << message << " Piotr.\n";
            break;

        case Name::Karol:
            std::cout << message << " Karol.\n";
            break;
        
        case Name::Aleksander:
            std::cout << message << " Aleksander.\n";
            break;

        case Name::Monika:
            std::cout << message << " Monika.\n";
            break;
        
        case Name::Magda:
            std::cout << message << " Magda.\n";
            break;

        case Name::Magdalena:
            std::cout << message << " Magdalena.\n";
            break;
        
        case Name::Beata:
            std::cout << message << " Beata.\n";
            break;
    }
}

int main()
{
    greetName("Jak tam", Name::Aleksander);
    greetName("Cześć", Name::Paweł);
    greetName("Co tam", Name::Monika);
    greetName("Dzień dobry", Name::Beata);

    return 0;
}