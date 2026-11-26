#include <format>
#include <fstream>
#include <random>

template <typename Distribution>
void generate(const std::string& filename, Distribution dist, std::mt19937& gen, int count = 1000)
{
    std::ofstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Nie można otworzyć pliku " + filename + "!");

    file << "val\n";
    for (int i = 0; i < count; i++)
        file << std::format("{}\n", dist(gen));
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    generate("zadanie4-uniform.csv",  std::uniform_real_distribution<double>(1, 10), gen);
    generate("zadanie4-binomial.csv", std::binomial_distribution<int>(20, 0.4), gen);
    generate("zadanie4-normal.csv",   std::normal_distribution<double>(0.0, 1.0), gen);

    return 0;
}
