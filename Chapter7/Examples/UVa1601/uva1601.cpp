// The morning after Halloween, Japan, 2007, UVa 1601 (2.189s)

#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <queue>
#include <cstring>
using namespace std;

constexpr int MAXH = 20;
constexpr int MAXW = 20;
constexpr int MAXN = 256+10;
constexpr int MAXCOMBO = 1<<24;
struct bfs_info {
    int fa[MAXN];
};
struct State {
    int s[3] = {0, 0, 0};
    int dist = -1;
    State() = default;
    bool operator==(const State &st) const
    {
        return memcmp(s, st.s, sizeof(s)) == 0;
    }
};

char Floor[MAXH][MAXW];
int G[MAXN][6];
int w, h, n;
int vis[MAXN][MAXN][MAXN];

bool valid_move(const State &s1, const State &s2)
{
    for (auto i = 0; i < 3; ++i)
        for (auto j = i+1; j < 3; ++j)
        {
            if (s2.s[i])
            {
                if (s2.s[i] == s2.s[j]) // step on the same square
                    return false;
                if (s1.s[i] == s2.s[j] && s1.s[j] == s2.s[i]) // swap position
                    return false;
            }
        }

    return true;
}

int main()
{
    G[0][0] = 1, G[0][1] = 0;
    while (scanf("%d %d %d\n", &w, &h, &n) == 3 && w)
    {
        for (auto i = 0; i < h; ++i)
            fgets(Floor[i], MAXW, stdin);

        State initial, goal;

        // Find starts and goals
        for (auto i = 0; i < h; ++i)
            for (auto j = 0; j < w; ++j)
            {
                int flatten = (i<<4)|j;
                if (islower(Floor[i][j]))
                    initial.s[Floor[i][j]-'a'] = flatten;
                else if (isupper(Floor[i][j]))
                    goal.s[Floor[i][j]-'A'] = flatten;

                if (Floor[i][j] != '#')
                {
                    int count = 0;
                    // right, up, left, down
                    if (j+1 < w-1 && Floor[i][j+1] != '#')
                        G[flatten][++count] = (i<<4)|(j+1);
                    if (i-1 > 0 && Floor[i-1][j] != '#')
                        G[flatten][++count] = ((i-1)<<4)|j;
                    if (j-1 > 0 && Floor[i][j-1] != '#')
                        G[flatten][++count] = (i<<4)|(j-1);
                    if (i+1 < h-1 && Floor[i+1][j] != '#')
                        G[flatten][++count] = ((i+1)<<4)|j;
                    G[flatten][++count] = flatten;
                    G[flatten][0] = count;
                }
            }


        queue<State> Q;
        initial.dist = 0;
        vis[initial.s[0]][initial.s[1]][initial.s[2]] = 1;
        Q.push(initial);

        while (!Q.empty())
        {
            const auto cur = Q.front(); Q.pop();
            const auto cur_dist = cur.dist;
            if (cur == goal)
            {
                printf("%d\n", cur_dist);
                break;
            }

            const int p0 = cur.s[0], p1 = cur.s[1], p2 = cur.s[2];
            auto next = cur;
            next.dist = cur_dist+1;
            for (auto i = 1; i <= G[p0][0]; ++i)
            {
                next.s[0] = G[p0][i];
                for (auto j = 1; j <= G[p1][0]; ++j)
                {
                    next.s[1] = G[p1][j];
                    for (auto k = 1; k <= G[p2][0]; ++k)
                    {
                        next.s[2] = G[p2][k];

                        if (!valid_move(cur, next))
                            continue;

                        int &h = vis[next.s[0]][next.s[1]][next.s[2]];
                        if (!h)
                        {
                            h = 1;
                            Q.push(next);
                        }
                    }
                }
            }
        }
        memset(vis, 0, sizeof(vis));
    }

    return 0;
}

// http://blog.csdn.net/acm_hkbu/article/details/42420503 (1.255s)
// http://blog.csdn.net/crazysillynerd/article/details/42562959 (1.366s)
// http://46aae4d1e2371e4aa769798941cef698.devproxy.yunshipei.com/crazysillynerd/article/details/42681579 (0.846s)
// http://www.bubuko.com/infodetail-955302.html (_w1: 0.495)
// http://www.aichengxu.com/view/78407 (0.896s)
// http://www.xlgps.com/article/114716.html (2.132s)
// http://www.cnblogs.com/20143605--pcx/p/4844828.html (1.959s)
// https://github.com/morris821028/UVa/blob/master/temp/1601%20-%20The%20Morning%20after%20Halloween%5Bbfs%5D.cpp
// https://github.com/morris821028/UVa/blob/master/temp/1601%20-%20The%20Morning%20after%20Halloween%5BDoubleBfs%5D.cpp
