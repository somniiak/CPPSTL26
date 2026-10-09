#include <algorithm>
#include <iostream>
#include <vector>

class Person
{
    private:
        std::string name;
        std::string surname;
        int year;

    public:
        Person(std::string name, std::string surname, int year) :
            name(name), surname(surname), year(year) {}

        friend bool operator<(const Person& a, const Person& b) {
            return std::tie(a.surname, a.name, a.year) <
                std::tie(b.surname, b.name, b.year );
        }

        friend std::ostream& operator<<(std::ostream& os, const Person& person) {
            os << person.surname << " " << person.name << " (ur. " << person.year << ")";
            return os;
        }
};

int main()
{
    std::vector<Person> people = {
        Person("Bruno", "Schulz", 1892),
        Person("Nick", "Wilde", 1984),
        Person("Marek", "Grechuta", 1945),
        Person("Bolesław", "Leśmian", 1877),
        Person("Violetta", "Villas", 1983),
        Person("Kurt", "Cobain", 1967),
        Person("Nelly", "Furtado", 1978),
    };

    std::sort(people.begin(), people.end());


    for(auto person : people)
        std::cout << person << "\n";

    return 0;
}