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

constexpr int MAXH = 18;
constexpr int MAXW = 18;
constexpr int MAXN = 150;

struct bfs_info {
    int dist[MAXN];
} fbfs_paths[3], bbfs_paths[3];
char Floor[MAXH][MAXW];
int G[MAXN][6];
int w, h, n;
int vis[MAXN][MAXN][MAXN];
int vis_b[MAXN][MAXN][MAXN];
int delta[][2] = {{0, 1},{0, -1}, {-1, 0}, {1, 0}};

struct State_f {
    static int N;
    int s[3];
    int dist;
    State_f() = default;
    bool operator==(const State_f &st) const
    {
        return memcmp(s, st.s, sizeof(s)) == 0;
    }
    bool operator< (const State_f &st) const
    {
        // return distance() > st.distance();
        auto da = distance(), db = st.distance();
        if (da != db)
            return da > db;
        return dist > st.dist;
    }
    int distance() const
    {
        int h_max = 0;
        for (auto i = 0; i < N; ++i)
            h_max = max(h_max, fbfs_paths[i].dist[s[i]]);
        return dist+h_max;
    }
};
struct State_b {
    static int N;
    int s[3];
    int dist;
    State_b() = default;
    bool operator==(const State_b &st) const
    {
        return memcmp(s, st.s, sizeof(s)) == 0;
    }
    bool operator< (const State_b &st) const
    {
        // return distance() > st.distance();
        auto da = distance(), db = st.distance();
        if (da != db)
            return da > db;
        return dist > st.dist;
    }
    int distance() const
    {
        int h_max = 0;
        for (auto i = 0; i < N; ++i)
            h_max = max(h_max, bbfs_paths[i].dist[s[i]]);
        return dist+h_max;
    }
};
int State_f::N;
int State_b::N;

template<class State>
bool valid_move(const State &s1, const State &s2)
{
    for (auto i = 0; i < State::N; ++i)
        for (auto j = i+1; j < State::N; ++j)
        {
            if (s2.s[i] == s2.s[j]) // step on the same square
                return false;
            if (s1.s[i] == s2.s[j] && s1.s[j] == s2.s[i]) // swap position
                return false;
        }

    return true;
}

int main()
{
    G[0][0] = 1, G[0][1] = 0;
    while (scanf("%d %d %d\n", &w, &h, &n) == 3 && w)
    {
        State_f::N = State_b::N = n;
        for (auto i = 0; i < h; ++i)
            fgets(Floor[i], MAXW, stdin);

        State_f initial{0, 0, 0, 0};
        State_b goal{0, 0, 0, 0};

        // Find starts and goals
        int cnt = 0;
        int id[MAXH][MAXW]; int x[MAXN]; int y[MAXN];
        for (auto i = 0; i < h; ++i)
            for (auto j = 0; j < w; ++j)
            {
                if (Floor[i][j] != '#')
                {
                    ++cnt;
                    x[cnt] = i; y[cnt] = j;  id[i][j] = cnt;
                    if (islower(Floor[i][j]))
                        initial.s[Floor[i][j]-'a'] = cnt;
                    else if (isupper(Floor[i][j]))
                        goal.s[Floor[i][j]-'A'] = cnt;
                }
            }

        for (auto j = 1; j <= cnt ; ++j)
        {
            int count = 0;
            for (auto di = 0; di < 4; ++di)
            {
                auto I = x[j]+delta[di][0], J = y[j]+delta[di][1];
                if (Floor[I][J] != '#')
                    G[j][++count] = id[I][J];
            }
            G[j][++count] = j;
            G[j][0] = count;
        }
        // find individual paths
        for (auto i = 0; i < n; ++i)
        {
            int vis[MAXN] = {0};
            queue<int> Q;
            vis[goal.s[i]] = 1;
            fbfs_paths[i].dist[goal.s[i]] = 0;
            Q.push(goal.s[i]);
            while (!Q.empty())
            {
                int cur = Q.front(); Q.pop();
                int cur_dist = fbfs_paths[i].dist[cur];

                for (auto ch = 1; ch < G[cur][0]; ++ch)
                {
                    auto nextcount = G[cur][ch];
                    if (!vis[nextcount])
                    {
                        fbfs_paths[i].dist[nextcount] = cur_dist+1;
                        vis[nextcount]= 1;
                        Q.push(nextcount);
                    }
                }
            }
        }
        for (auto i = 0; i < n; ++i)
        {
            int vis[MAXN] = {0};
            queue<int> Q;
            vis[initial.s[i]] = 1;
            bbfs_paths[i].dist[initial.s[i]] = 0;
            Q.push(initial.s[i]);
            while (!Q.empty())
            {
                int cur = Q.front(); Q.pop();
                int cur_dist = bbfs_paths[i].dist[cur];

                for (auto ch = 1; ch < G[cur][0]; ++ch)
                {
                    auto nextcount = G[cur][ch];
                    if (!vis[nextcount])
                    {
                        bbfs_paths[i].dist[nextcount] = cur_dist+1;
                        vis[nextcount]= 1;
                        Q.push(nextcount);
                    }
                }
            }
        }

        priority_queue<State_f> Qf;
        priority_queue<State_b> Qb;
        initial.dist = 0, goal.dist = 0;
        memset(vis, -1, sizeof(vis));
        memset(vis_b, -1, sizeof(vis_b));
        vis[initial.s[0]][initial.s[1]][initial.s[2]] = 0;
        vis_b[goal.s[0]][goal.s[1]][goal.s[2]] = 0;
        Qf.push(initial);
        Qb.push(goal);

        while (!Qf.empty() || !Qb.empty())
        {
            // forwards
            auto cur = Qf.top(); Qf.pop();
            auto cur_dist = cur.dist;
            int p0 = cur.s[0], p1 = cur.s[1], p2 = cur.s[2];
            if (vis_b[p0][p1][p2] != -1)
            {
                printf("%d\n", cur_dist+vis_b[p0][p1][p2]);
                break;
            }

            if (vis[p0][p1][p2] < cur_dist)
                continue;
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
                        int &v = vis[next.s[0]][next.s[1]][next.s[2]];
                        // v > cur_dist+1 can actually happen! it is a balance of g and h cost func.
                        if (v==-1 || v > cur_dist+1)
                        {
                            v = cur_dist+1;
                            Qf.push(next);
                        }
                    }
                }
            }
            // backwards
            auto cur_b = Qb.top(); Qb.pop();
            cur_dist = cur_b.dist;
            p0 = cur_b.s[0], p1 = cur_b.s[1], p2 = cur_b.s[2];
            if (vis[p0][p1][p2] != -1)
            {
                printf("%d\n", cur_dist+vis[p0][p1][p2]);
                break;
            }

            if (vis_b[p0][p1][p2] < cur_dist)
                continue;
            auto next_b = cur_b;
            next_b.dist = cur_dist+1;
            for (auto i = 1; i <= G[p0][0]; ++i)
            {
                next_b.s[0] = G[p0][i];
                for (auto j = 1; j <= G[p1][0]; ++j)
                {
                    next_b.s[1] = G[p1][j];
                    for (auto k = 1; k <= G[p2][0]; ++k)
                    {
                        next_b.s[2] = G[p2][k];
                        if (!valid_move(cur_b, next_b))
                            continue;
                        int &v = vis_b[next_b.s[0]][next_b.s[1]][next_b.s[2]];
                        // v > cur_dist+1 can actually happen! it is a balance of g and h cost func.
                        if (v==-1 || v > cur_dist+1)
                        {
                            v = cur_dist+1;
                            Qb.push(next_b);
                        }
                    }
                }
            }
        }
    }

    return 0;
}

