// Just Finish it up, UVa11093

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (auto cas = 1; cas <= T; ++cas)
    {
        int N; cin >> N;
        vector<int> pi(N), qi(N);
        for (auto i = 0; i < N; ++i)
            cin >> pi[i];
        for (auto i = 0; i < N; ++i)
            cin >> qi[i];

        int ans = 0;
        bool possible = false;
        while (ans < N)
        {
            int petrol = 0;
            int i = 0;
            for (; i < N; ++i)
            {
                auto station = (ans+i) % N;
                petrol += pi[station];
                petrol -= qi[station];
                if (petrol < 0)
                    break;
            }

            if (i == N)
            {
                possible = true;
                break;
            }

            ans += i+1;
        }

        cout << "Case " << cas << ": ";
        if (possible)
            cout << "Possible from station " << ans+1 << "\n";
        else
            cout << "Not possible\n";
    }

    return 0;
}


