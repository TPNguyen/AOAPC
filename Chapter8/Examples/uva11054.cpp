// Wine Trading in Gergovia, UVa 11054

#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    while (cin >> n && n)
    {
        int a, cum_tot = 0;
        long long total = 0;

        while (n--)
        {
            cin >> a;
            cum_tot += a;
            total += abs(cum_tot);
        }

        cout << total << "\n";
    }

    return 0;
}

