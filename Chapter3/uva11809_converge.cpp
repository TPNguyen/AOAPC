#include <cmath>
#include <string>
#include <iostream>

constexpr double LOG2_10 = std::log2(10);
constexpr double eps = 1e-6;
int main()
{
    double ment;
    unsigned long expo, M, E;
    std::string line;
    while (std::cin >> line)
    {
        if (line == "0e0") break;

        auto ie = line.find('e');
        if (ie == std::string::npos) break;
        ment = std::stod(line.substr(0, ie));
        expo = std::stol(line.substr(ie+1));

        double log2_exp = LOG2_10 * expo + std::log2(ment);
        for (M = 0; M < 10; ++M)
        {
            double log2_ment = std::log2(1 - 1.0/(1 << (M + 1)));
            E = (unsigned long)std::round(std::log2(log2_exp - log2_ment + 1));
            if (std::fabs(log2_exp - ((1 << E)-1) - log2_ment) < eps)
                break;
        }
        std::cout << M << ' ' << E << "\n";
    }

    return 0;
}


