#include <iostream>
#include <string>

int main()
{
    int N = 0;
    std::cin >> N;
    auto first = true;
    while(N--)
    {
        std::string line;
        std::cin >> line;

        using ssize = std::string::size_type;
        auto len = line.size();
        for (ssize p = 1; p <= len; ++p)
        {
            if (len % p == 0)
            {
                auto ok = true;
                for (ssize s = 0; ok && s < p; ++s)
                    for (ssize j = s+p; ok && j < len; j += p)
                        if (line[s] != line[j])
                        {
                            ok = false;
                            break;
                        }
                if (ok)
                {
                    if (first) first = false;
                    else std::cout << "\n";
                    std::cout << p << "\n";
                    break;
                }
            }
        }
    }

    return 0;
}

