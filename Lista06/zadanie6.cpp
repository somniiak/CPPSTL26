#include <print>
#include <stdexcept>
#include <string>
#include <format>
#include <tuple>
#include <vector>

class Person
{
    std::string _name, _surname;
    int _age, _weight;
    double _height;

    public:
        Person(const std::string& name, const std::string& surname, int age, int weight, double height) :
        _name(name), _surname(surname), _age(age), _weight(weight), _height(height)
        {
            if (name.empty() || surname.empty())
                throw std::invalid_argument("Imię i nazwisko nie mogą być puste!");
            if (age <= 0 || weight <= 0 || height <= 0)
                throw std::invalid_argument("Wiek, waga i wzrost nie mogą być niedodatnie!");
        }

        const std::string& getName() const { return _name; }
        const std::string& getSurname() const { return _surname; }
        int getAge() const { return _age; }
        int getWeight() const { return _weight; }
        double getHeight() const { return _height; }
};

std::tuple<std::string, int, double> initialsAgeBmi(const Person& p)
{
    return {
        std::string{p.getName().front(), p.getSurname().front()},
        p.getAge(),
        p.getWeight() / p.getHeight() / p.getHeight()
    };
}

std::tuple<int, int, double> ageWeightHeight(const Person& p)
{
    return {p.getAge(), p.getWeight(), p.getHeight()};
}

std::tuple<std::string, std::string, int> nameSurnameAge (const Person& p)
{
    return {p.getName(), p.getSurname(), p.getAge()};
}

int main()
{
    std::vector<Person> people = {
      Person("Marek", "Kucharek", 35, 110, 1.68),
      Person("Ala", "Makota", 20, 70, 1.75),
    };


    // Iteracja po tupli
    // https://stackoverflow.com/a/54053084

    for (const Person& p : people)
    {
        auto [initials, age, bmi] = initialsAgeBmi(p);
        std::println("{}, {}, {:.2f}", initials, age, bmi);

        auto tuple2 = ageWeightHeight(p);
        std::apply([](const auto&... args) {
            (std::print("{} ", args), ...);
        }, tuple2);
        std::println();

        auto tuple3 = nameSurnameAge(p);
        std::apply([](const auto&... args) {
            (std::print("{} ", args), ...);
        }, tuple3);
        std::println("\n");
    }

    return 0;
}
