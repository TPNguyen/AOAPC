// The morning after Halloween, Japan, 2007, UVa 1601 (2.072s)

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
constexpr int MAXN = 150;
constexpr int MAXCOMBO = 1<<24;
struct bfs_info {
    int fa[MAXN];
};
struct State {
    int s[3];
    int dist;
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
int delta[][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

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

        State initial{0, 0, 0, 0}, goal{0, 0, 0, 0};

        // Find starts and goals
        int count = 0;
        for (auto i = 0; i < h; ++i)
            for (auto j = 0; j < w; ++j)
            {
                if (Floor[i][j] != '#')
                {
                    ++count;
                    if (islower(Floor[i][j]))
                        initial.s[Floor[i][j]-'a'] = count;
                    else if (isupper(Floor[i][j]))
                        goal.s[Floor[i][j]-'A'] = count;
                    Floor[i][j] = count;
                }
                else
                    Floor[i][j] = 0;
            }

        for (auto i = 0; i < h; ++i)
            for (auto j = 0; j < w; ++j)
            {
                count = 0;
                if (Floor[i][j])
                {
                    auto flatten = Floor[i][j];
                    // right, up, left, down
                    if (Floor[i][j+1])
                        G[flatten][++count] = Floor[i][j+1];
                    if (Floor[i-1][j])
                        G[flatten][++count] = Floor[i-1][j];
                    if (Floor[i][j-1])
                        G[flatten][++count] = Floor[i][j-1];
                    if (Floor[i+1][j])
                        G[flatten][++count] = Floor[i+1][j];
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
                if (n > 1) {
                    for (auto j = 1; j <= G[p1][0]; ++j)
                    {
                        next.s[1] = G[p1][j];
                        if (n > 2) {
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
                        else {
                            if (!valid_move(cur, next))
                                continue;
                            int &h = vis[next.s[0]][next.s[1]][0];
                            if (!h)
                            {
                                h = 1;
                                Q.push(next);
                            }

                        }
                    }
                }
                else {
                    if (!valid_move(cur, next))
                        continue;
                    int &h = vis[next.s[0]][0][0];
                    if (!h)
                    {
                        h = 1;
                        Q.push(next);
                    }
                }
            }
        }
        memset(vis, 0, sizeof(vis));
    }

    return 0;
}

