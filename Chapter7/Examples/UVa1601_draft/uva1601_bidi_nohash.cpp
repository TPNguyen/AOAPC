// The morning after Halloween, Japan, 2007, UVa 1601

#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <cstring>
using namespace std;

constexpr int MAXH = 20;
constexpr int MAXW = 20;
constexpr int MAXN = 256+10;
struct bfs_info {
    int fa[MAXN];
};
struct State {
    int s[3] = {0, 0, 0};
    State() = default;
    State(int p1, int p2, int p3)
    {
        s[0] = p1, s[1] = p2, s[2] = p3;
    }
    bool operator==(const State &st) const
    {
        return memcmp(s, st.s, sizeof(s)) == 0;
    }

    size_t Hasher() const
    {
        size_t val = 0;
        for (const auto &ij: s)
        {
            val <<= 8;
            val += ij;
        }
        return val;
    }
};

char Floor[MAXH][MAXW];
int G[MAXN][6];
int w, h, n;
int dist_f[MAXN][MAXN][MAXN];
int dist_b[MAXN][MAXN][MAXN];

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
    while (scanf("%d %d %d\n", &w, &h, &n) == 3 && w)
    {
        for (auto i = 0; i < h; ++i)
            fgets(Floor[i], MAXW, stdin);

        // Find starts and goals
        map<int, int> lowercase;
        map<int, int> uppercase;
        G[0][0] = 0, G[0][1] = -1;
        for (auto i = 0; i < h; ++i)
            for (auto j = 0; j < w; ++j)
            {
                if (islower(Floor[i][j]))
                    lowercase.insert({Floor[i][j], (i<<4)+j});
                else if (isupper(Floor[i][j]))
                    uppercase.insert({Floor[i][j], (i<<4)+j});

                if (Floor[i][j] != '#')
                {
                    int count = 0;
                    int flatten = (i<<4)+j;
                    // right, up, left, down
                    if (j+1 < w-1 && Floor[i][j+1] != '#')
                        G[flatten][count++] = (i<<4)+j+1;
                    if (i-1 > 0 && Floor[i-1][j] != '#')
                        G[flatten][count++] = ((i-1)<<4)+j;
                    if (j-1 > 0 && Floor[i][j-1] != '#')
                        G[flatten][count++] = (i<<4)+j-1;
                    if (i+1 < h-1 && Floor[i+1][j] != '#')
                        G[flatten][count++] = ((i+1)<<4)+j;
                    G[flatten][count++] = (i<<4)+j;
                    G[flatten][count] = -1;
                }
            }

        int count = 0;
        State initial;
        for (auto &i: lowercase)
            initial.s[count++] = i.second;
        count = 0;
        State goal;
        for (auto &g: uppercase)
            goal.s[count++] = g.second;

        // unordered_map<int, int> dist_f, dist_b;
        queue<State> Qf, Qb; // front, back
        Qf.push(initial);
        Qb.push(goal);
        dist_f[initial.s[0]][initial.s[1]][initial.s[2]] = 0;
        dist_b[goal.s[0]][goal.s[1]][goal.s[2]] = 0;

        while (!Qf.empty() && !Qb.empty())
        {
            auto cur = Qf.front(); Qf.pop();
            auto cur_dist = dist_f[cur.s[0]][cur.s[1]][cur.s[2]];
            if (dist_b[cur.s[0]][cur.s[1]][cur.s[2]]) // alreday in back queue
            {
                printf("%d\n", cur_dist+dist_b[cur.s[0]][cur.s[1]][cur.s[2]]);
                break;
            }

            int p0 = cur.s[0], p1 = cur.s[1], p2 = cur.s[2];
            auto next = cur;
            for (auto i = 0; G[p0][i] >= 0; ++i)
            {
                next.s[0] = G[p0][i];
                for (auto j = 0; G[p1][j] >= 0; ++j)
                {
                    next.s[1] = G[p1][j];
                    for (auto k = 0; G[p2][k] >= 0; ++k)
                    {
                        next.s[2] = G[p2][k];

                        if (valid_move(cur, next))
                        {
                            int &d = dist_f[next.s[0]][next.s[1]][next.s[2]];
                            if (d == 0)
                            {
                                d = cur_dist+1;
                                Qf.push(next);
                            }
                        }
                    }
                }
            }

            cur = Qb.front(); Qb.pop();
            cur_dist = dist_b[cur.s[0]][cur.s[1]][cur.s[2]];
            if (dist_f[cur.s[0]][cur.s[1]][cur.s[2]]) // alreday in front queue
            {
                printf("%d\n", cur_dist+dist_f[cur.s[0]][cur.s[1]][cur.s[2]]);
                break;
            }

            p0 = cur.s[0], p1 = cur.s[1], p2 = cur.s[2];
            next = cur;
            for (auto i = 0; G[p0][i] >= 0; ++i)
            {
                next.s[0] = G[p0][i];
                for (auto j = 0; G[p1][j] >= 0; ++j)
                {
                    next.s[1] = G[p1][j];
                    for (auto k = 0; G[p2][k] >= 0; ++k)
                    {
                        next.s[2] = G[p2][k];

                        if (valid_move(cur, next))
                        {
                            int &d = dist_b[next.s[0]][next.s[1]][next.s[2]];
                            if (d == 0)
                            {
                                d = cur_dist+1;
                                Qb.push(next);
                            }
                        }
                    }
                }
            }
        }
        memset(dist_f, 0, sizeof(dist_f));
        memset(dist_b, 0, sizeof(dist_b));
    }

    return 0;
}

