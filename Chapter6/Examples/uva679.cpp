// Dropping balls, UVa 679

#include <iostream>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    int D, I;
    while (n--)
    {
        cin >> D >> I;
        --I;
        int ans = 1 << (D-1);
        for (auto leftshift = D-2; I != 0 && leftshift >= 0; --leftshift)
        {
            ans += (I%2) << leftshift;
            I /= 2;
        }

        cout << ans << "\n";
    }

    return 0;
}


