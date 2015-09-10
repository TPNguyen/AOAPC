#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

int main()
{
    const int MAXN = 10;
    int r, c;
    char crsw[MAXN][MAXN];
    int kase = 0;
    while (std::cin >> r >> c)
    {
        if (r == 0) break;
        std::vector<std::vector<int>> nums(r, std::vector<int>(c,0));
        int eligible = 0;
        for (auto i = 0; i < r; ++i)
            for (auto j = 0; j < c; ++j)
            {
                std::cin >> crsw[i][j];
                if (crsw[i][j] != '*')
                {
                    if (j == 0 || i == 0 || crsw[i][j-1] == '*' || crsw[i-1][j] == '*')
                        nums[i][j] = ++eligible;
                }
            }


        if (kase)
            std::cout << "\n";
        std::cout << "puzzle #" << ++kase << ":\n";

        // find the "Across" words definition
        std::cout << "Across\n";
        for (auto i = 0; i < r; ++i)
            for (auto j = 0; j < c; ++j)
            {
                if (nums[i][j] && (j == 0 || crsw[i][j-1] == '*')) // is a cross word start
                {
                    std::cout << std::setw(3) << nums[i][j] << ".";
                    std::string w{crsw[i][j]};
                    for (auto k = j+1; k < c && crsw[i][k] != '*'; ++k)
                        w += crsw[i][k];

                    std::cout << w << "\n";
                }
            }

        // find the "Down" words definitions
        std::cout << "Down\n";
        for (auto i = 0; i < r; ++i)
            for (auto j = 0; j < c; ++j)
            {
                if (nums[i][j] && (i == 0 || crsw[i-1][j] == '*')) // is a down word start
                {
                    std::cout << std::setw(3) << nums[i][j] << ".";
                    std::string w{crsw[i][j]};
                    for (auto k = i+1; k < r && crsw[k][j] != '*'; ++k)
                        w += crsw[k][j];

                    std::cout << w << "\n";
                }
            }
    }

    return 0;
}

