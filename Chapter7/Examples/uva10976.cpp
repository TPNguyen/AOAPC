// Fractions Again?!, UVa 10976
// y can only be in [k+1, 2k]

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int k;
    while (cin >> k)
    {
        vector<pair<int, int>> res;
        for (auto y = k+1; y <= 2*k; ++y)
        {
            if (k*y % (y-k) == 0)
                res.push_back({k*y/(y-k), y});
        }
        cout << res.size() << "\n";
        for (auto &p: res)
            cout << "1/" << k << " = " << "1/" << p.first << " + " << "1/" << p.second << "\n";
    }

    return 0;
}
