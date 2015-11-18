// Symmetry, ACM/ICPC Seoul 2004, UVa1595

#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    using num_xsum = pair<int, int>;
    int T, N, x, y;
    cin >> T;
    while (T--)
    {
        cin >> N;
        unordered_map<int, num_xsum> y2x;
        for (auto i = 0; i < N; ++i)
        {
            cin >> x >> y;
            auto ins_res = y2x.insert({y, {1, x}});
            if (ins_res.second == false)
            {
                ++(ins_res.first->second.first);
                ins_res.first->second.second += x;
            }
        }

        bool symmetric = true;
        auto it = y2x.cbegin();
        auto it_end = y2x.cend();
        const int numx = it->second.first;
        const int sumx = it->second.second;

        for ( ++it; it != it_end; ++it)
        {
            if (sumx * it->second.first != it->second.second * numx)
            {
                symmetric = false;
                break;
            }

        }

        if (symmetric)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}

            
