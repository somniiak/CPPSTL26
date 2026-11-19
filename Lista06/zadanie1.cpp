#include <algorithm>
#include <format>
#include <string>
#include <deque>
#include <print>

class Person
{
    std::string _name, _surname;
    int _age, _weight;
    double _height;

    public:
        Person(const std::string& name, const std::string& surname, int age, int weight, double height) :
        _name(name), _surname(surname), _age(age), _weight(weight), _height(height) { }

        const std::string toString() const
        {
            return std::format("Person({}, {}, {}, {}, {})", _name, _surname, _age, _weight, _height);
        }

        const std::string& getName() const { return _name; }
        const std::string& getSurname() const { return _surname; }
        int getAge() const { return _age; }
        int getWeight() const { return _weight; }
        double getHeight() const { return _height; }

        void setWeight(int newWeight) { _weight = newWeight; }
};

int main()
{
    auto stringDequePerson = [&](const std::deque<Person>& people) {
        std::string peopleString;

        for(const Person& p : people)
            peopleString += std::format("  {}\n", p.toString());

        return std::format("std::deque<Person>(\n{})", peopleString);
    };

    std::deque<Person> people = {
        Person("Alicja", "Malik", 42, 67, 1.70),
        Person("Jerzy", "Nawieży", 70, 72, 1.75),
        Person("Andrzej", "Sienkiewicz", 89, 132, 1.88),
        Person("Bartłomiej", "Rykoszewicz", 28, 115, 1.90),
        Person("Agata", "Batat", 24, 52, 1.65),
        Person("Marianna", "Gołczewska", 78, 89, 1.72),
        Person("Krystyna", "Bors", 65, 85, 1.71),
        Person("Kamil", "Dudzik", 18, 84, 1.86),
        Person("Aleksander", "Pobudka", 21, 60, 1.68),
        Person("Agnieszka", "Litwin", 26, 74, 1.69),
        Person("Maja", "Bogusz", 23, 55, 1.65),
        Person("Dominik", "Kowalski", 24, 123, 1.89),
    };

    std::println("1. Oryginalne wartości\n");
    std::println("{}\n", stringDequePerson(people));

    // Sortowanie po BMI (weight / height^2)
    std::sort(people.begin(), people.end(), [&](const Person& p1, const Person& p2) {
        double bmi1 = p1.getWeight() / p1.getHeight() / p1.getHeight();
        double bmi2 = p2.getWeight() / p2.getHeight() / p2.getHeight();
        return bmi1 < bmi2;
    });

    std::println("2. Sortowanie po BMI\n");
    std::println("{}\n", stringDequePerson(people));

    std::for_each(people.begin(), people.end(), [](Person& p) {
        p.setWeight(static_cast<int>(p.getWeight() * 0.9));
    });

    std::println("3. Utrata 10% wagi po obozie\n");
    std::println("{}\n", stringDequePerson(people));

    auto it = std::stable_partition(people.begin(), people.end(), [](const Person& p) {
       return p.getWeight() > 100;
    });

    std::println("4. Podział na osoby lekkie i ciężkie\n");
    std::println("Osoby lekkie:\n{}\n", stringDequePerson(std::deque<Person>(it, people.end())));
    std::println("Osoby ciężkie:\n{}\n", stringDequePerson(std::deque<Person>(people.begin(), it)));

    auto youngest = std::min_element(people.begin(), people.end(), [](const Person& p1, const Person& p2) {
        return p1.getAge() < p2.getAge();
    });

    auto oldest = std::max_element(people.begin(), people.end(), [](const Person& p1, const Person& p2) {
        return p1.getAge() < p2.getAge();
    });

    std::println("5. Osoba najmłodsza i najstarsza\n");
    std::println("Osoba najmłodsza: {}", youngest->toString());
    std::println("Osoba najstarsza: {}\n", oldest->toString());

    return 0;
}
