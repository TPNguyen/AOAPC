// Patrol Robot, ACM/ICPC Hanoi 2006, UVa 1600

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

constexpr int MAX = 22;
struct Coor {
    int I, J, K; // K is continuous obstacles
};

int di[] = {-1, 0, 0, 1};
int dj[] = {0, 1, -1, 0};

int main()
{
    ios_base::sync_with_stdio(false);
    int N; cin >> N;
    while (N--)
    {
        int Grid [MAX][MAX];
        int d[MAX][MAX][MAX];
        int m, n, k; cin >> m >> n >> k;
        for (auto i = 1; i <= m; ++i)
            for (auto j = 1; j <= n; ++j)
                cin >> Grid[i][j];
        memset(d, -1, sizeof(d));

        queue<Coor> Q;
        Q.push({1, 1, 0});
        d[1][1][0] = 0;

        int ans = -1;
        while (!Q.empty())
        {
            auto p = Q.front();
            if (p.I == m && p.J == n)
            {
                ans = d[m][n][p.K];
                break;
            }
            Q.pop();

            for (auto i = 0; i < 4; ++i)
            {
                auto newi = p.I + di[i];
                auto newj = p.J + dj[i];
                auto newk = Grid[newi][newj] ? p.K + 1 : 0;
                if (newi < 1 || newi > m || newj < 1 || newj > n) // out of bound
                    continue;
                if (newk > k || d[newi][newj][newk] != -1) // already visited
                    continue;
                else
                {
                    d[newi][newj][newk] = d[p.I][p.J][p.K]+1;
                    Q.push({newi, newj, newk});
                }
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
