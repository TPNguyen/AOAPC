// Ideal Path, NEERC 2010, UVa 1599
// https://github.com/morris821028/UVa/blob/master/temp/1599%20-%20Ideal%20Path.cpp
// http://blog.csdn.net/kun768/article/details/43450043
// http://blog.csdn.net/wcr1996/article/details/43637917
// http://www.cnblogs.com/AOQNRMGYXLMV/p/4267038.html
// http://www.cnblogs.com/jerryRey/p/4598113.html


#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m)
    {
        vector<vector<pair<int, int>>> G(n+1);
        for (auto i = 0; i < m; ++i)
        {
            int a, b, c;
            cin >> a >> b >> c;
            G[a].push_back({c, b});
            G[b].push_back({c, a});
        }

        /*for (auto &n: G)
            sort(n.begin(), n.end());*/

        vector<pair<int, int>> parents(n+1); // {node#, color connecting node#/i}
        vector<int> vis(n+1);
        vector<int> dist(n+1);
        parents[1] = {1, 0};
        vis[1] = 1;
        dist[1] = 0;

        queue<int> Q;
        Q.push(1);
        while (!Q.empty())
        {
            auto node = Q.front(); Q.pop();
            if (node == n)
                break;
            auto cur_color = parents[node].second;
            auto cur_dist = dist[node];
            vector<int> equal_color_equal_dist{node};
            while (!Q.empty())
            {
                if (cur_color == parents[Q.front()].second && cur_dist == dist[Q.front()])
                {
                    equal_color_equal_dist.push_back(Q.front());
                    Q.pop();
                }
                else
                    break;
            }
            vector<pair<int,int>> sorted_children;
            for (auto eced: equal_color_equal_dist)
            {
                for (auto &next: G[eced])
                {
                    if (vis[next.second]) continue;
                    if (parents[next.second].first == 0 || next.first < parents[next.second].second)
                        parents[next.second] = {eced, next.first};
                    dist[next.second] = dist[eced]+1;
                    sorted_children.push_back(next);
                }
            }
            sort(sorted_children.begin(), sorted_children.end());
            for (const auto &nc: sorted_children)
            {
                if (vis[nc.second]) continue;
                vis[nc.second] = 1;
                Q.push(nc.second);
            }
        }

        auto len = dist[n];
        vector<int> path_color(len);
        for (auto i = len-1; i >= 0; --i)
        {
            path_color[i] = parents[n].second;
            n = parents[n].first;
        }

        cout << len << "\n";
        cout << path_color[0];
        for (auto i = 1; i < len; ++i)
            cout << " " << path_color[i];
        cout << "\n";
    }


    return 0;
}



