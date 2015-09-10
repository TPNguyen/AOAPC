#include <sstream>
#include <iostream>
#include <vector>

int main()
{
    int T = 0;
    std::cin >> T;
    while (T--)
    {
        int N = 0;
        std::cin >> N;
        std::ostringstream os;
        for (auto i = 1; i <= N; ++i)
            os << i;
        std::vector<int> num_digits(10, 0);
        for (const auto c: os.str())
        {
            ++num_digits[c-'0'];
        }

        auto first = true;
        for (const auto c: num_digits)
        {
            if (first) first = false;
            else std::cout << " ";
            std::cout << c;
        }
        std::cout << "\n";
    }

    return 0;
}
