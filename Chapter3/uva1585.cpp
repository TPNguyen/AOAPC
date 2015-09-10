#include <iostream>
#include <string>

int main()
{
    int T = 0;
    std::cin >> T;
    while (T--)
    {
        std::string xo;
        std::cin >> xo;

        int final_score = 0;
        int running_score = 0;
        for (const auto c: xo)
        {
            if (c == 'X')
                running_score = 0;
            else if (c == 'O')
            {
                ++running_score;
                final_score += running_score;
            }
        }

        std::cout << final_score << "\n";
    }

    return 0;
}

