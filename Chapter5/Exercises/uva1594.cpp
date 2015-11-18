// Ducci Sequence, ACM/ICPC Seoul 2009, UVa1594

#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
#include <utility>
using namespace std;

constexpr int MAXN = 15;
int main()
{
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    while (T--)
    {
        int n; cin >> n;
        vector<int> Tuple(n);
        vector<int> Tuple_swp(n);
        vector<int> zeros(n);
        for (auto i = 0; i < n; ++i)
            cin >> Tuple[i];

        set<vector<int>> tuples {Tuple};

        bool found_zero = false;
        bool found_loop = false;
        for (auto i = 0; i < 1000; ++i)
        {
            for (auto j = 0; j < n-1; ++j)
                Tuple_swp[j] = abs(Tuple[j] - Tuple[j+1]);
            Tuple_swp[n-1] = abs(Tuple[n-1] - Tuple[0]);

            if (Tuple_swp == zeros)
            {
                found_zero = true;
                break;
            }
            auto insert_p = tuples.insert(Tuple_swp);
            if (insert_p.second == false)
            {
                found_loop = true;
                break;
            }

            using std::swap;
            swap(Tuple, Tuple_swp);
        }

        if (found_loop)
            cout << "LOOP\n";
        else
            cout << "ZERO\n";
    }

    return 0;
}

