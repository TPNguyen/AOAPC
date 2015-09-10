#include <iostream>
#include <string>

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        std::string s;
        std::cin >> s;
        std::string ans = s;

        for (auto i = 1; i < s.size(); ++i)
        {
            std::string temp = s.substr(i) + s.substr(0,i);
            if (temp < ans)
                ans = std::move(temp);
        }

        std::cout << ans << "\n";
    }

    return 0;
}

