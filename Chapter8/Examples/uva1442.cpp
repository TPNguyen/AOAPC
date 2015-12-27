// Cave, ACM/ICPC CERC 2009, UVa 1442

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int Z; cin >> Z;
    while (Z--)
    {
        int n; cin >> n;
        vector<int> fl(n), cel(n);
        for (auto i = 0; i < n; ++i)
            cin >> fl[i];
        for (auto i = 0; i < n; ++i)
            cin >> cel[i];

        vector<int> heights(n);
        int level = cel.front();
        for (auto i = 0; i < n; ++i)
        {
            if (level < fl[i]) level = fl[i];
            else // if (level > cel[i]) level = cel[i];
                level = std::min(level, cel[i]);

            heights[i] = level;
        }

        int ans = 0;
        level = cel.back();
        for (auto i = n-1; i >= 0; --i)
        {
            if (level < fl[i]) level = fl[i];
            else // if (level > cel[i]) level = cel[i];
                level = std::min(level, cel[i]);

            ans += std::min(heights[i], level) - fl[i];
        }

        cout << ans << '\n';
    }

    return 0;
}

