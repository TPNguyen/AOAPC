#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;
int main()
{
    // preset a table for each M and E
    double A[16][32];
    long B[16][32];
    constexpr double LOG10_2 = log10(2);

    for (auto i = 0; i < 10; ++i)
        for (auto j = 1; j <= 30; ++j)
        {
            auto mentisa = 1 - exp2(-i-1);
            auto expo = exp2(j) - 1;
            auto log10_sum = log10(mentisa) + expo * LOG10_2;
            B[i][j] = trunc(log10_sum);
            A[i][j] = pow(10, log10_sum - B[i][j]);
        }

    /*for (auto i = 0; i < 10;  ++i)
        for (auto j = 1; j <=30; ++j)
            cout << fixed << setprecision(15) << A[i][j] << 'e' << B[i][j] << "\n";
            */


    string line;
    while (std::cin >> line)
    {
        if (line == "0e0") break;

        auto ment = std::stod(line.substr(0, 17));
        auto expo = std::stol(line.substr(18));

        for (auto i = 0; i < 10; ++i)
            for (auto j = 1; j <= 30; ++j)
                if (expo == B[i][j] && fabs(ment - A[i][j]) < 1e-4)
                {
                    cout << i << " " << j << "\n";
                    break;
                }
    }

    return 0;
}
