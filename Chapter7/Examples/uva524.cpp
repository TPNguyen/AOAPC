// Prime Ring Problem, UVa 524

#include <iostream>
using namespace std;

constexpr int MAXN = 18;
int N;
int res[MAXN];
int vis[MAXN];
bool primes[MAXN];

bool is_prime(int n);
void dfs(int level);
int main()
{
    ios_base::sync_with_stdio(false);
    for (auto i = 3; i <= 2*MAXN; i += 2)
        primes[i] = is_prime(i);
    int kase = 0;
    while (cin >> N)
    {
        if (kase)
            cout << "\n";
        cout << "Case " << ++kase << ":\n";
        res[1] = 1;
        dfs(2);
    }

    return 0;
}

bool is_prime(int n)
{
    for (auto i = 2; i*i <= n; ++i)
        if (n % i == 0)
            return false;
    return true;
}

void dfs(int level)
{
    // try all possible candidate for cur level
    for (auto i = 2; i <= N; ++i)
    {
        if (vis[i])
            continue;

        if (primes[res[level-1] + i])
        {
            if (level == N && primes[i+1])
            {
                // solution found
                for (auto i = 1; i < N; ++i)
                    cout << res[i] << " ";
                cout << i << "\n";
                break;
            }
            else
            {
                res[level] = i;
                vis[i] = 1;
                dfs(level+1);
                vis[i] = 0;
            }
        }
    }
}



