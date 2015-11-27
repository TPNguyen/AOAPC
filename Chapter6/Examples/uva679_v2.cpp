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
        int iend = 1;
        int ibegin = (ans >> 1);
        while (iend <= I)
        {
            if (I & iend)
                ans += ibegin;
            iend <<= 1;
            ibegin >>= 1;
        }

        cout << ans << "\n";
    }

    return 0;
}



