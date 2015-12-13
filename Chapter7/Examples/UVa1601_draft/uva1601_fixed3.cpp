// The morning after Halloween, Japan, 2007, UVa 1601

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
int vis[MAXN][MAXN][MAXN];
// int delta[][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

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

        // unordered_set<int> vis;
        // queue<int> dist;
        // queue<State> Q;
        vector<int> dist;
        vector<State> Q;
        int front = 0, rear = 1;
        Q.push_back(initial);
        dist.push_back(0);
        // vis.insert(initial.Hasher());
        vis[initial.s[0]][initial.s[1]][initial.s[2]] = 1;

        while (front < rear)
        {
            const auto cur = Q[front];// Q.pop();
            const auto cur_dist = dist[front];// dist.pop();
            if (cur == goal)
            {
                printf("%d\n", cur_dist);
                break;
            }

            const int p0 = cur.s[0], p1 = cur.s[1], p2 = cur.s[2];
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

                        if (!valid_move(cur, next))
                            continue;

                        // bool inserted = false;
                        // std::tie(std::ignore, inserted) = vis.insert(next.Hasher());
                        // if (inserted)
                        int &h = vis[next.s[0]][next.s[1]][next.s[2]];
                        if (!h)
                        {
                            h = 1;
                            Q.push_back(next);
                            dist.push_back(cur_dist+1);
                            rear++;
                        }
                    }
                }
            }
            front++;
        }
        memset(vis, 0, sizeof(vis));
    }

    return 0;
}

/*
        // find individual paths
        vector<bfs_info> bfs_paths(n);
        for (auto i = 0; i < n; ++i)
        {
            int vis[MAXN] = {0};
            queue<int> Q;
            vis[goal.s[i]] = 1;
            bfs_paths[i].fa[goal.s[i]] = goal.s[i];
            Q.push(goal.s[i]);
            while (!Q.empty())
            {
                int cur = Q.front(); Q.pop();
                if (cur == initial.s[i]) continue;
                int ii = cur/16, ij = cur%16;

                // right, up, left, down
                for (auto ch = 0; ch < 4; ++ch)
                {
                    auto I = ii+delta[ch][0];
                    auto J = ij+delta[ch][1];
                    auto flat = (I<<4)+J;
                    if (I > 0 && I < h && J > 0 && J < w && !vis[flat] && Floor[I][J] != '#')
                    {
                        bfs_paths[i].fa[flat] = cur;
                        vis[flat]= 1;
                        Q.push(flat);
                    }
                }
            }
        }

                    */
