#include <iostream>
#include <map>
#include <string>
#include <algorithm>

int main()
{
    int T;
    std::cin >> T;
    int m, n;
    while (T--)
    {
        if (std::cin >> m >> n && m && n)
        {
            std::string DNAs[m];
            for (auto i = 0; i < m; ++i)
                std::cin >> DNAs[i];

            std::string ans;
            int c_error = 0;
            for (auto i = 0; i < n; ++i)
            {
                std::map<char, int> consensus_c;
                for (auto j = 0; j < m; ++j)
                    ++consensus_c[DNAs[j][i]];
                auto it = std::max_element(consensus_c.cbegin(), consensus_c.cend(), [](const typename std::map<char, int>::value_type &a, const typename std::map<char, int>::value_type &b) { return a.second < b.second; });
                if (it != consensus_c.cend())
                    ans += it->first;
                c_error += m - it->second;
            }

            std::cout << ans << "\n" << c_error << "\n";
        }
    }

    return 0;
}
