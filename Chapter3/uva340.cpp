#include <iostream>
#include <vector>

int main()
{
    const int MAXN = 1010;
    int n;
    int game = 0;
    std::vector<int> ans(MAXN);
    std::vector<int> guess(MAXN);
    while (std::cin >> n && n)
    {
        ++game;
        std::cout << "Game " << game << ":\n";
        // get answer sequence
        int num;
        for (auto i = 0; i < n; ++i)
        {
            std::cin >> num;
            ans[i] = num;
        }
        // get guess sequence
        for(;;)
        {
            for (auto i = 0; i < n; ++i)
            {
                std::cin >> num;
                guess[i] = num;
            }
            auto valid_guess = false;
            for (auto i: guess)
            {
                if (i)
                {
                    valid_guess = true;
                    break;
                }
            }

            if (valid_guess)
            {
                int A = 0, B = 0;
                for (auto i = 0; i < n; ++i)
                    if (ans[i] == guess[i])
                        ++A;

                for (auto d = 1; d <= 9; ++d)
                {
                    auto c1 = 0, c2 = 0;
                    for (auto i = 0; i < n; ++i)
                    {
                        if (ans[i] == d) ++c1;
                        if (guess[i] == d) ++c2;
                    }
                    B += std::min(c1, c2);
                }

                std::cout <<"   (" << A << "," << B-A << ")\n";
            }
            else
                break;
        }
    }

    return 0;
}

