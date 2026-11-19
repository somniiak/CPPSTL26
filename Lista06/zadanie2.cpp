#include <algorithm>
#include <cstdint>
#include <format>
#include <list>
#include <string>
#include <print>

class Point
{
    std::string _name;
    double _x, _y;
    uint8_t _r, _g, _b;

    public:
        Point(const std::string& name, double x, double y, uint8_t r, uint8_t g, uint8_t b) :
        _name(name), _x(x), _y(y), _r(r), _g(g), _b(b) { }

        const std::string toString() const
        {
            return std::format("Point(name={}, x={}, y={}, r={}, g={}, b={})", _name, _x, _y, _r, _g, _b);
        }

        const std::string getName() const { return _name; }
        double getX() const { return _x; }
        double getY() const { return _y; }
        uint8_t getR() const { return _r; }
        uint8_t getG() const { return _g; }
        uint8_t getB() const { return _b; }
};

int main()
{
    auto stringListPoint = [](const std::list<Point>& points) {
        std::string pointsString;

        for (const Point& p : points)
            pointsString += std::format("  {}\n", p.toString());

        return std::format("std::list<Point>(\n{})", pointsString);
    };

    std::list<Point> points = {
      Point("Red", -12.3, 23.2, 229, 20, 0),
      Point("Crimson", -3.1, -4.3, 162, 0, 37),
      Point("Orange", 0, 12.5, 250, 104, 0),
      Point("Amber", 1.4, 3.7, 240, 163, 10),
      Point("Gold", -9.4, -8.7, 255, 215, 0),
      Point("Yellow", 3, 0, 227, 200, 0),
      Point("Lime", 5, 0, 164, 196, 0),
      Point("Olive", -4.8, 20.2, 109, 135, 100),
      Point("Green", 0, 0, 96, 169, 23),
      Point("Emerald", 3.4, 9.7, 0, 138, 0),
      Point("Teal", 12.3, -12.2, 0, 171, 169),
      Point("Aqua", 8.4, 12.9, 0, 255, 255),
      Point("Cyan", -6.9, -6.9, 27, 161, 226),
      Point("Cobalt", 6.7, -6.7, 0, 80, 239),
      Point("Navy", 0, -9.33, 0, 0, 128),
      Point("Indigo", -4.2, 3.7, 106, 0, 255),
      Point("Violet", 5.7, 9.8, 170, 0, 255),
      Point("Magenta", 12.3, 9.4, 216, 0, 115),
      Point("Pink", 3.4, -4.2, 244, 114, 208),
      Point("Mauve", -7.3, -0.6, 118, 96, 138),
      Point("Steel", 21.1, 20.9, 100, 118, 135),
      Point("Taupe", -4.3, -2.3, 135, 121, 78),
      Point("Brown", 6.1, -2.3, 130, 90, 44),
    };

    std::println("1. Oryginalne wartości\n");
    std::println("{}\n", stringListPoint(points));

    std::erase_if(points, [](const Point& p) {
        return p.getName().length() > 5;
    });

    std::println("2. Bez nazw >5 znaków\n");
    std::println("{}\n", stringListPoint(points));

    // Pierwsza ćwiartka
    auto q1 = std::count_if(points.begin(), points.end(), [](const Point& p) {
        return p.getX() > 0 && p.getY() > 0;
    });

    // Druga ćwiartka
    auto q2 = std::count_if(points.begin(), points.end(), [](const Point& p) {
        return p.getX() < 0 && p.getY() > 0;
    });

    // Trzecia ćwiartka
    auto q3 = std::count_if(points.begin(), points.end(), [](const Point& p) {
        return p.getX() < 0 && p.getY() < 0;
    });

    // Czwarta ćwiartka
    auto q4 = std::count_if(points.begin(), points.end(), [](const Point& p) {
        return p.getX() > 0 && p.getY() < 0;
    });

    // Na osiach
    auto onAxis = std::count_if(points.begin(), points.end(), [](const Point& p) {
        return p.getX() == 0 || p.getY() == 0;
    });

    std::println("3. Ile punktów na ćwiartce?\n");
    std::println("Ćwiartka I: {}", q1);
    std::println("Ćwiartka II: {}", q2);
    std::println("Ćwiartka III: {}", q3);
    std::println("Ćwiartka IV: {}", q4);
    std::println("Na osiach układu: {}\n", onAxis);

    auto luminance = [](const Point& p) {
        return p.getR() * 0.3 + p.getG() * 0.59 + p.getB() * 0.11;
    };

    points.sort([&luminance](const Point& p1, const Point& p2) {
        return luminance(p1) < luminance(p2);
    });

    std::println("4. Sortowanie po luminacji\n");
    std::println("{}\n", stringListPoint(points));

    auto it = std::stable_partition(points.begin(), points.end(), [&luminance](const Point& p) {
        return luminance(p) < 64;
    });

    // https://en.cppreference.com/cpp/container/list/splice
    // Transfers elements from one list to another
    std::list<Point> darkPoints;
    darkPoints.splice(darkPoints.begin(), points, points.begin(), it);

    std::println("5. Ciemne punkty\n");
    std::println("Ilość: {}\n", darkPoints.size());
    std::println("{}\n", stringListPoint(darkPoints));

    return 0;
}
