#include <iostream>
#include <string>

int main()
{
    std::string s, t;
    while (std::cin >> s >> t)
    {
        bool is_sub = true;
        using ssizeT = std::string::size_type;
        ssizeT pos = 0;
        for (const auto &c : s)
        {
            auto tpos = t.find_first_of(c, pos);
            if (std::string::npos == tpos)
            {
                is_sub = false;
                break;
            }
            pos = tpos+1;
        }

        if (is_sub)
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }

    return 0;
}

