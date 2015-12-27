// Defense Lines, ACM/ICPC CERC 2010, UVa1471

#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstring>
using namespace std;

constexpr int MAXN = 200004;
unsigned int towerheights[MAXN];
unsigned int M[MAXN]; // towerheights[k] such that g[k] == j (j: index into M)
unsigned int f[MAXN]; // towerheights[k] such that g[k] == j (j: index into M)
int main()
{
    ios_base::sync_with_stdio(false);

    int Z; cin >> Z;
    while (Z--)
    {
        int N; cin >> N;
        for (auto i = 1; i <= N; ++i)
            cin >> towerheights[i];
        memset(M+1, -1, sizeof(unsigned int)*N);

        f[N] = 0;
        for (auto i = N-1; i > 0; --i)
        {
            if (towerheights[i+1] > towerheights[i])
                f[i] = f[i+1]+1;
            else
                f[i] = 0;
        }

        M[0] = 0;
        unsigned int maxL = 0, maxgj = 0;
        unsigned int increase_count = 0;
        unsigned int j = 1;
        for (auto i = 1; i <= N; ++i)
        {
            if (towerheights[i] > towerheights[i-1])
                ++increase_count;
            else
            {
                increase_count = 1;
                j = 1;
            }
            j = distance(M, lower_bound(M+j, M+maxgj+1, towerheights[i]));
            maxL = max(maxL, j+f[i]);
            M[increase_count]  = min(M[increase_count], towerheights[i]);
            maxgj = max(increase_count, maxgj);
        }

        cout << maxL << "\n";
    }
    return 0;
}
                        /*if (increase_count > maxgj)
                        {
                            M[increase_count] = towerheights[i];
                            maxgj++;
                        }
                        else
                            M[increase_count]  = min(M[increase_count], towerheights[i]);
                            */
            // if (j > maxgj) // can extend the last longest increasing seq
                // if (increase_count >= j)
                /*auto n = i+1;
                for (; n < N; ++n)
                {
                    if (towerheights[n] > towerheights[n-1])
                    {
                        increase_count++; j++;
                        maxL = max(maxL, j);
                        M[increase_count]  = min(M[increase_count], towerheights[n]);
                        maxgj = max(increase_count, maxgj);
                    }
                    else
                        break;
                }
                increase_count = 0;
                i = n;
                */
