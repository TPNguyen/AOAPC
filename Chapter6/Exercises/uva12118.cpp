// Inspector's Dilemma, ACM/ICPC Dhaka 2007, UVa 12118
// Even if there are separate components, we need one edge to connect one odd degree node from
// previous component to the next. Therefore, one additional edge == two odd degree nodes.
// If a component is itselt a Euler circuit, we can imagine that we split a even degree node into
// two 1 degree nodes, each one connecting to previous/next components or act as the end of the
// wholy connected single component.

// http://morris821028.github.io/2014/08/29/oj/uva/uva-12118/ (very clear!)
// http://blog.csdn.net/wcr1996/article/details/43309671 (He tries to explain but his Chinese is less clear than his code)
// http://www.aichengxu.com/view/43734
// http://www.cnblogs.com/20143605--pcx/p/4864181.html
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

constexpr int MAXV = 1024;
vector<int> G[MAXV];
int vis[MAXV];

int dfs(int i);
int main()
{
    ios_base::sync_with_stdio(false);
    int V, E, T, Kase = 0;
    // Reserve doesn't really help. If trying to reserve 1000 is actually worse...
    /*for (auto i = 1; i < MAXV; ++i)
        G[i].reserve(512);*/
    while (cin >> V >> E >> T && V)
    {
        for (auto i = 0; i < E; ++i)
        {
            int a, b;
            cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
        }

        int tot_odd_degree_nodes = 0;
        for (auto i = 1; i <= V; ++i)
        {
            if (!vis[i] && !G[i].empty()) // a new component
                tot_odd_degree_nodes += max(2, dfs(i)); // return number of odd degree nodes
        }

        cout << "Case " << ++Kase << ": " << T*(E + max(0, tot_odd_degree_nodes/2-1)) << "\n";
        memset(vis, 0, sizeof(vis));
        for (auto i = 1; i <= V; ++i)
            G[i].clear();
    }

    return 0;
}

int dfs(int i)
{
    int ret = G[i].size() % 2;
    vis[i] = 1;

    for (auto next: G[i])
    {
        if (!vis[next])
            ret += dfs(next);
    }

    return ret;
}
