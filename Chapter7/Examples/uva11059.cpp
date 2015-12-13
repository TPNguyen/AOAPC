// Maximum Product, UVa 11059

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int N, Kase = 0;
    while (cin >> N)
    {
        vector<int> seq(N);
        for (auto &s: seq)
            cin >> s;

        long long max_prod = 0;
        for (auto s = 0; s < N; ++s)
        {
            for (auto e = s+1; e <= N; ++e)
            {
                long long prod = 1;
                for (auto i = s; i != e; ++i)
                {
                    prod *= seq[i];
                    if (prod > max_prod)
                        max_prod = prod;
                }
            }
        }

        cout << "Case #" << ++Kase << ": The maximum product is " << max_prod << ".\n\n";
    }

    return 0;
}
