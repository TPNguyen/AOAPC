// Zombie's Treasure Chest, Shanghai 2011, UVa12325

#include <iostream>
#include <algorithm>
using namespace std;

long long gcd (long long a, long long b)
{
    return b? gcd(b, a%b): a;
}

int main()
{
    ios_base::sync_with_stdio(false);
    long long T, N, S1, V1, S2, V2, kase = 0; cin >> T;
    while (T--)
    {
        cin >> N >> S1 >> V1 >> S2 >> V2;
        if (S1 < S2)
            swap(S1, S2), swap(V1, V2);
        long long maxiter = N/S1;
        long long gcd_ss = gcd(S1, S2);
        long long s1 = S1/gcd_ss-1, s2 = S2/gcd_ss-1;
        if (V1*S2 < V2*S1)
            maxiter = min(maxiter, s2);
        else if (s1 < maxiter)
        {
            maxiter = s1;
            swap(S1, S2), swap(V1, V2);
        }

        long long ans = 0;
        for (auto i = 0; i <= maxiter; ++i)
        {
            ans = max(ans, (i)*V1 + (N-i*S1)/S2*V2);
        }

        cout << "Case #" << ++kase << ": " << ans << "\n";
    }

    return 0;
}
