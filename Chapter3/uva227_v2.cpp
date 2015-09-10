#include <iostream>
#include <utility>
#include <string>

// tested performace of not using putback.
// result : no change...
int main()
{
    std::string pzle[5];
    int Kase = 0;
    char c;
    while (true)
    {
        auto x = -1, y = -1;
        std::getline(std::cin, pzle[0]);
        if (pzle[0][0] == 'Z') break;
        for (auto i = 1; i < 5; ++i)
            std::getline(std::cin, pzle[i]);
        for(auto i = 0; i < 5; ++i)
        {
            for (auto j = 0; j < 5; ++j)
            {
                if (pzle[i][j] == ' ')
                {
                    x = i;
                    y = j;
                }
            }
        }
        //std::cout << "x = " << x << "\n" << "y = " << y << "\n";

        auto valid_move = true;
        while (std::cin >> c && c != '0')
        {
            if (valid_move) {
                if (c == 'A')
                {
                    if (x-1 >= 0) {
                        std::swap(pzle[x][y], pzle[x-1][y]); x--;
                    }
                    else
                        valid_move = false;
                }
                else if (c == 'B')
                {
                    if (x+1 < 5) {
                        std::swap(pzle[x][y], pzle[x+1][y]); x++;
                    }
                    else
                        valid_move = false;
                }
                else if (c == 'R')
                {
                    if (y+1 < 5) {
                        std::swap(pzle[x][y], pzle[x][y+1]); y++;
                    }
                    else
                        valid_move = false;
                }
                else if (c == 'L')
                {
                    if (y-1 >= 0) {
                        std::swap(pzle[x][y], pzle[x][y-1]); y--;
                    }
                    else
                        valid_move = false;
                }
                else
                    valid_move = false;
            }

            /*std::cout << "letter : " << c << "\n";
            for (auto i = 0; i < 5; ++i)
            {
                for (auto j = 0; j < 5; ++j)
                    std::cout << pzle[i][j];
                std::cout << "\n";
            }
            std::cout << "\n";*/
        }
        // swallow the newline so that next read line doens't get empty line
        std::cin.ignore(100, '\n');

        if (Kase)
            std::cout << "\n";
        std::cout << "Puzzle #" << ++Kase << ":\n";
        if (valid_move) {
            for (auto i = 0; i < 5; ++i)
            {
                for(auto j = 0; j < 5; ++j)
                {
                    if (j) std::cout << ' ';
                    std::cout << pzle[i][j];
                }
                std::cout << "\n";
            }
        }
        else
        {
            std::cout << "This puzzle has no final configuration.\n";
        }
    }

    return 0;
}

