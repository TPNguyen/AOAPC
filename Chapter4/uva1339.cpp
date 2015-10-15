#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::string A, B;
    std::vector<int> cntA(26,0), cntB(26,0);
    while (std::cin >> A >> B)
    {
        for (const auto c: A)
            ++cntA[c-'A'];
        for (const auto c: B)
            ++cntB[c-'A'];

        std::sort(cntA.begin(), cntA.end());
        std::sort(cntB.begin(), cntB.end());

        if (cntA == cntB)
            std::cout << "YES\n";
        else
            std::cout << "NO\n";

        std::fill(cntA.begin(), cntA.end(), 0);
        std::fill(cntB.begin(), cntB.end(), 0);
    }

    return 0;
}

