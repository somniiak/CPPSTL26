#include <cmath>
#include <complex>
#include <print>

const double EULER_GAMMA = 0.5772156649;

std::complex<double> gamma(std::complex<double> z, int times)
{
    std::complex<double> result = std::exp(-EULER_GAMMA * z) / z;

    for (int i = 1; i <= times; i++)
    {
        std::complex<double> t = z / static_cast<double>(i);
        result *= std::exp(t) / (1.0 + t);
    }

    return result;
}

std::complex<double> inv_gamma(std::complex<double> z, int times)
{
    std::complex<double> result = std::exp(EULER_GAMMA * z) * z;

    for (int i = 1; i <= times; i++)
    {
        std::complex<double> t = z / static_cast<double>(i);
        result *= (1.0 + t) / std::exp(t);
    }

    return result;
}

int main()
{
    constexpr std::complex<double> points[] = {
        {6.7, 6.9}, {4.2, -4.2}, {-21.37, 21.37}
    };

    for (int n : {10, 100, 1000})
    {
        for (std::complex<double> z : points)
        {
            auto res = gamma(z, n);
            auto inv_res = inv_gamma(z, n);

            std::println("gamma(({}, {}), {}) = ({}, {})",
                z.real(), z.imag(), n, res.real(), res.imag());
            std::println("inv_gamma(({}, {}), {}) = ({}, {})",
                z.real(), z.imag(), n, inv_res.real(), inv_res.imag());
        }

        std::println();
    }

    return 0;
}
