// Defense Lines, ACM/ICPC CERC 2010, UVa1471

#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstring>
using namespace std;

constexpr int MAXN = 200004;
unsigned int towerheights[MAXN];
unsigned int M[MAXN]; // towerheights[k] such that g[k] == j (j: index into M)
unsigned int f[MAXN]; // f[i]
unsigned int ff[MAXN]; // g[i]
int main()
{
    ios_base::sync_with_stdio(false);

    int Z; cin >> Z;
    while (Z--)
    {
        int N; cin >> N;
        for (auto i = 1; i <= N; ++i)
            cin >> towerheights[i];
        // memset(M+1, -1, sizeof(unsigned int)*N);

        f[N] = 0;
        for (auto i = N-1; i > 0; --i)
        {
            if (towerheights[i+1] > towerheights[i])
                f[i] = f[i+1]+1;
            else
                f[i] = 0;
        }
        ff[0] = 0;
        for (auto i = 1; i <= N; ++i)
        {
            if (towerheights[i] > towerheights[i-1])
                ff[i] = ff[i-1]+1;
            else
                ff[i] = 1;
        }

        M[0] = 0;
        unsigned int maxL = 0, maxgj = 0;
        unsigned int increase_count = 0;
        unsigned int j;
        for (auto i = 1; i <= N; ++i)
        {
            if (ff[i] == 1)
                j = 1;
            j = distance(M, lower_bound(M+j, M+maxgj+1, towerheights[i]));
            maxL = max(maxL, j+f[i]);
            if (j <= ff[i])
                M[ff[i]]  = towerheights[i];
            maxgj = max(ff[i], maxgj);
        }

        cout << maxL << "\n";
    }
    return 0;
}

