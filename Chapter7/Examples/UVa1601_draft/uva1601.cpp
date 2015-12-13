// The morning after Halloween, Japan, 2007, UVa 1601

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <iterator>
using namespace std;

constexpr int MAXH = 20;
constexpr int MAXW = 20;
string Floor[MAXH];

using IJ = pair<int, int>;

int Hash(const vector<IJ> &pos);
int main()
{
    ios_base::sync_with_stdio(false);
    int w, h, n;
    while (cin >> w >> h >> n && w)
    {
        cin.ignore(100, '\n');
        for (auto i = 0; i < h; ++i)
            getline(cin, Floor[i]);

        map<int, IJ> lowercase;
        map<int, IJ> uppercase;
        vector<IJ> G[MAXH][MAXW];
        for (auto i = 0; i < h; ++i)
            for (auto j = 0; j < w; ++j)
            {
                if (islower(Floor[i][j]))
                    lowercase.insert({Floor[i][j], {i, j}});
                if (isupper(Floor[i][j]))
                    uppercase.insert({Floor[i][j], std::make_pair(i, j)});

                if (Floor[i][j] != '#')
                {
                    G[i][j].push_back({i, j});
                    // right, up, left, down
                    if (j+1 < w-1 && Floor[i][j+1] != '#')
                        G[i][j].push_back({i, j+1});
                    if (i-1 > 0 && Floor[i-1][j] != '#')
                        G[i][j].push_back({i-1, j});
                    if (j-1 > 0 && Floor[i][j-1] != '#')
                        G[i][j].push_back({i, j-1});
                    if (i+1 < h-1 && Floor[i+1][j] != '#')
                        G[i][j].push_back({i+1, j});
                }
            }
        vector<IJ> initial;
        for (auto &i: lowercase)
            initial.push_back(std::move(i.second));
        vector<IJ> goal;
        for (auto &g: uppercase)
            goal.push_back(std::move(g.second));
        unordered_set<int> vis;
        vector<int> dist;

        vector<vector<IJ>> Q;
        int front = 0, rear = 1;
        Q.push_back(initial);
        vis.insert(Hash(initial));
        dist.push_back(0);

        while (front < rear)
        {
            const auto cur = Q[front];
            if (cur == goal)
                break;

            const auto &p0 = cur[0];
            for (auto i = 0; i < G[p0.first][p0.second].size(); ++i)
            {
                IJ mov0 = G[p0.first][p0.second][i];
                if (n > 1)
                {
                    const auto &p1 = cur[1];
                    for (auto j = 0; j < G[p1.first][p1.second].size(); ++j)
                    {
                        IJ mov1 = G[p1.first][p1.second][j];
                        if (n > 2)
                        {
                            const auto &p2 = cur[2];
                            for (auto k = 0; k < G[p2.first][p2.second].size(); ++k)
                            {
                                IJ mov2 = G[p2.first][p2.second][k];
                                if (mov0 == mov1 || mov0 == mov2 || mov1 == mov2) continue; // can't move to same loc
                                if (p0 == mov1 && p1 == mov0 || p0 == mov2 && p2 == mov0 || p1 == mov2 && p2 == mov1) continue;
                                vector<IJ> next{std::move(mov0), std::move(mov1), std::move(mov2)};
                                bool inserted = false;
                                std::tie(std::ignore, inserted) = vis.insert(Hash(next));
                                if (inserted)
                                {
                                    Q.push_back(std::move(next));
                                    dist.push_back(dist[front]+1);
                                    rear++;
                                }
                            }
                        }
                        else
                        {
                            if (mov0 == mov1) continue;
                            if (p0 == mov1 && p1 == mov0) continue;
                            vector<IJ> next{mov0, mov1};
                            bool inserted = false;
                            std::tie(std::ignore, inserted) = vis.insert(Hash(next));
                            if (inserted)
                            {
                                Q.push_back(std::move(next));
                                dist.push_back(dist[front]+1);
                                rear++;
                            }
                        }
                    }
                }
                else
                {
                    if (mov0 == p0) continue;
                    vector<IJ> next{mov0};
                    vis.insert(Hash(next));
                    Q.push_back(std::move(next));
                    dist.push_back(dist[front]+1);
                    rear++;
                }
            }
            front++;
        }

        cout << dist[front] << endl;
    }

    return 0;
}

int Hash(const vector<IJ> &pos)
{
    int val = 0;
    for (const auto &ij: pos)
    {
        val <<= 8;
        val += ij.first << 4;
        val += ij.second;
    }

    return val;
}

