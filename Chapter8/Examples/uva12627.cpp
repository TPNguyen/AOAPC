// Erratic Expansion, UVa 12627

#include <iostream>
#include <cmath>
using namespace std;

long long f(int K, int X);
long long g(int K, int X);
long long solve(int K, int A, int B);

int main()
{
    ios_base::sync_with_stdio(false);
    int T, K, A, B;  cin >> T;
    for (auto cas = 1; cas <= T; ++cas)
    {
        cin >> K >> A >> B;
        // cout << "Case " << cas << ": " << solve(K, A, B) << "\n";
        cout << "Case " << cas << ": " << f(K, B) - f(K, A-1) << "\n";
    }

    return 0;
}

long long solve(int K, int A, int B)
{
    if (K == 0) return 1;
    auto half = 1 << (K-1);
    if (A <= half && B <= half)
        return 2*(g(K-1, half-A+1) - g(K-1, half-B));
    if (A > half && B > half)
        return f(K-1, B-half) - f(K-1, A-half-1);

    return f(K-1, B-half) + 2*g(K-1, half-A+1);
}

long long all_red(int K)
{
    long long ans = 1;
    for (auto i = 1; i <= K; ++i)
        ans *= 3;

    return ans;
}
long long g(int K, int X)
{
    if (X == 0) return 0;
    if (K == 0) return 1;
    auto half = 1 << (K-1);

    if (X > half)
        return 2*g(K-1, X-half) + static_cast<long long>(pow(3, K-1));
    else
        return g(K-1, X);
}

long long f(int K, int X)
{
    if (X == 0) return 0;
    if (K == 0) return 1;
    auto half = 1 << (K-1);

    if (X > half)
       // return f(K-1, X-half) + 2*static_cast<long long>(pow(3, K-1));
        return f(K-1, X-half) + 2*all_red(K-1);
    else
        return 2*(f(K-1, X));
}





