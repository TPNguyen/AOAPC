// Fill, UVa 10603

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;

constexpr int MAXS = 202;
struct Node {
    int poured;
    int state[3];
    bool operator< (const Node &n) const
    {
        return poured > n.poured;
    }
    /*Node(int v1, int v2, int v3)
    {
        state[0] = v1, state[1] = v2, state[2] = v3;
    }*/
};

int Cap[3];
int vis[MAXS][MAXS];
int vol2poured[MAXS];

void solve(int a, int b, int c, const int d);
int main()
{
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    while (T--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        Cap[0] = a, Cap[1] = b, Cap[2] = c;
        solve(a, b, c, d);
    }

    return 0;
}

inline void fill_ans(const Node &n)
{
    for (auto i = 0; i < 3; ++i)
    {
        if (vol2poured[n.state[i]] == -1)//  || vol2poured[n.state[i]] > n.poured // no need to check, n.poured can't be less
        {
            // assert(vol2poured[n.state[i]] <= n.poured);
            vol2poured[n.state[i]] = n.poured;
        }
    }
}


void solve(int a, int b, int c, int d)
{
    memset(vis, 0, sizeof(vis));
    memset(vol2poured, -1, sizeof(vol2poured));

    Node first{0, 0, 0, c};
    priority_queue<Node> Q;
    vis[0][0] = 1;
    Q.push(first);

    while (!Q.empty())
    {
        auto n = Q.top(); Q.pop();
        fill_ans(n);
        if (vol2poured[d] != -1)
            break;

        for (auto i = 0; i < 3; ++i)
            for (auto j = 0; j < 3; ++j)
            {
                if (i == j || n.state[i] == 0 || n.state[j] == Cap[j])
                    continue;

                int amount = min(Cap[j], n.state[i]+n.state[j]) - n.state[j];
                Node next(n);
                next.state[i] -= amount;
                next.state[j] += amount;
                next.poured += amount;
                if (vis[next.state[0]][next.state[1]]) // cannot have lower amount of water poured
                    continue;
                else
                {
                    vis[next.state[0]][next.state[1]] = 1;
                    Q.push(next);
                }
            }
    }

    while (d >= 0) // Note: d can be zero!
    {
        if (vol2poured[d] != -1)
        {
            cout << vol2poured[d] << " " << d << '\n';
            return ;
        }
        d--;
    }

}






