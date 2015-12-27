// 4 Values Whose Sum is Zero, ACM/ICPC SWERC 2005, UVa 1152

#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>
using namespace std;

array<int, 4010> A, B, C, D;

int main()
{
    ios_base::sync_with_stdio(false);
    int Tests; cin >> Tests;
    while (Tests--)
    {
        int n; cin >> n;
        for (auto i = 0; i < n; ++i)
            cin >> A[i] >> B[i] >> C[i] >> D[i];

        unordered_map<int, int> aplusb;

        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < n; ++j)
                aplusb[A[i]+B[j]]++;

        int ans = 0;
        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < n; ++j)
            {
                auto it = aplusb.find(-(C[i]+D[j]));
                if (it != aplusb.end())
                    ans += it->second;
            }

        cout << ans << "\n";
        if (Tests) cout << "\n";
    }

    return 0;
}

