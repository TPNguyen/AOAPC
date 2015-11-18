
#include <iostream>
#include <vector>
using namespace std;

constexpr int MAXN = 16;
vector<int> Tuple(MAXN);
vector<int> Tuple_swp(MAXN);
// vector<int> zeros(MAXN);
int main()
{
    ios_base::sync_with_stdio(false);
    int T;  cin >> T;
    while (T--)
    {
        int n; cin >> n;
        for (auto i = 0; i < n; ++i)
            cin >> Tuple[i];

        bool found_zero = false;
        for (auto i = 0; i < 1000; ++i)
        {
            for (auto i = 0; i < n-1; ++i)
                Tuple_swp[i] = abs(Tuple[i] - Tuple[i+1]);
            Tuple_swp[n-1] = abs(Tuple[n-1] - Tuple[0]);

            found_zero = true;
            for (auto i = 0; i < n; ++i)
            {
                if (Tuple_swp[i] != 0)
                {
                    found_zero = false;
                    break;
                }
            }
            if (found_zero)
                break;

            using std::swap;
            swap(Tuple, Tuple_swp);
        }

        if (found_zero)
            cout << "ZERO\n";
        else
            cout << "LOOP\n";
    }

    return 0;
}

