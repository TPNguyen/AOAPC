// The morning after Halloween, Japan, 2007, UVa 1601

#include <cstdio>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <queue>
#include <cstring>
#include <cassert>
using namespace std;

constexpr int MAXH = 20;
constexpr int MAXW = 20;
constexpr int MAXN = 256+10;

struct bfs_info {
    int dist[MAXN] = {0};
} bfs_paths[3];

int weights[3];

struct State {
    static State go;
    int s[3] = {0, 0, 0};
    int dist = -1;
    State() = default;
    State(int p1, int p2, int p3)
    {
        s[0] = p1, s[1] = p2, s[2] = p3;
    }
    bool operator==(const State &st) const
    {
        return memcmp(s, st.s, sizeof(s)) == 0;
    }
    bool operator< (const State &st) const
    {
        auto thisdis = distance(), thatdis = st.distance();
        if (thisdis != thatdis)
            return thisdis > thatdis;
        return dist > st.dist;
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
    int distance() const
    {
        int ans = dist;
        int h = 0;
        for (auto i = 0; i < 3; ++i)
        {
            if (s[i])
                h = max(h, bfs_paths[i].dist[s[i]]);
        }
        return ans + h;
    }

};
State State::go;

char Floor[MAXH][MAXW];
int G[MAXN][6];
int w, h, n;
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
        initial.dist = 0;
        count = 0;
        State goal;
        for (auto &g: uppercase)
            goal.s[count++] = g.second;
        State::go = goal;

        // find individual paths
        memset(bfs_paths, 0, sizeof(bfs_paths));
        for (auto i = 0; i < n; ++i)
        {
            int vis[MAXN] = {0};
            queue<int> Q;
            vis[goal.s[i]] = 1;
            bfs_paths[i].dist[goal.s[i]] = 0;
            Q.push(goal.s[i]);
            while (!Q.empty())
            {
                int cur = Q.front(); Q.pop();
                int cur_dist = bfs_paths[i].dist[cur];
                int ii = cur/16, ij = cur%16;

                // right, up, left, down
                for (auto ch = 0; ch < 4; ++ch)
                {
                    auto I = ii+delta[ch][0];
                    auto J = ij+delta[ch][1];
                    auto flat = (I<<4)+J;
                    if (I > 0 && I < h && J > 0 && J < w && !vis[flat] && Floor[I][J] != '#')
                    {
                        bfs_paths[i].dist[flat] = cur_dist+1;
                        vis[flat]= 1;
                        Q.push(flat);
                    }
                }
            }

            weights[i] = bfs_paths[i].dist[initial.s[i]];
        }


        unordered_map<int, int> vis;
        priority_queue<State> Qf; // front, back
        Qf.push(initial);
        vis.insert({initial.Hasher(), initial.distance()});

        while (!Qf.empty())
        {
            auto cur = Qf.top(); Qf.pop();
            auto cur_dist = cur.dist;
            if (cur == goal) // alreday in back queue
            {
                printf("%d\n", cur_dist);
                break;
            }

            int p0 = cur.s[0], p1 = cur.s[1], p2 = cur.s[2];
            auto next = cur;
            next.dist = cur_dist+1;
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
                            bool inserted = false;
                            std::tie(std::ignore, inserted) = vis.insert({next.Hasher(), next.distance()});
                            if (inserted)
                                Qf.push(next);
                            // The following could happen!!!
                            else if (vis[next.Hasher()] > next.distance())
                            {
                                // int oldv = vis[next.Hasher()];
                                // assert(false);
                                Qf.push(next);
                                vis[next.Hasher()] = next.distance();
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}

