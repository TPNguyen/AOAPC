#include <cmath>
#include <iostream>

int main()
{
    double ment;
    long expo;
    std::string line;
    constexpr double LOG2_10 = std::log2(10);
    constexpr double eps = 1e-6; // this is by trial and error from input uva11809.all300 generated from uva11809_table.cpp
/* pow(10, on E = 17, 18, 20, 24, 28, 29) has big differences from the actual values
0 1
0 2
0 3
0 4
0 5
0 6
0 7
0 8
0 9
0 10
0 11
0 12
0 13
0 14
0 15
0 16
36 17
35 18
0 19
33 20
0 21
0 22
0 23
28 24
0 25
0 26
0 27
25 28
23 29
0 30
*/
    while (std::cin >> line)
    {
        if (line == "0e0") break;

        ment = std::stod(line.substr(0, 17));
        expo = std::stol(line.substr(18));

        double log2_exp = LOG2_10 * expo + std::log2(ment);
        // calculate 2^E-1
        int high_E = std::ceil(log2_exp);

        // std::cout << log2_exp << " " << high_E << " ";

        // test to see if mentisa is exactly 0.5 (0.1 base2)
        if (std::fabs(high_E - log2_exp) < eps)
            ++high_E;
        int E = std::log2(high_E + 1) + 0.5;

        // std::cout << E << ' ';

        // mentisa log2
        double log2_ment = log2_exp - high_E;
        double base2_ment = std::exp2(log2_ment);    // = 1-2^-n
        // std::cout << log2_ment <<  " " << base2_ment << " " << 1-base2_ment << "\n";
        int M = -std::log2(1-base2_ment) - 0.5;

        std::cout << M << ' ' << E << "\n";
    }

    return 0;
}

