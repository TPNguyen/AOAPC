// Paintball, UVa 11853
// https://github.com/morris821028/UVa/blob/master/temp/11853%20-%20Paintball.cpp

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

constexpr double H = 1000;
constexpr int MAXN = 1024;
struct Circle {
    double x, y, r;
};
vector<int> vis;
vector<Circle> nodes;
vector<vector<int>> G;

bool circle_overlap(const Circle &c1, const Circle &c2)
{
    auto dx = c1.x-c2.x;
    auto dy = c1.y-c2.y;
    auto sr = c1.r+c2.r;
    return dx*dx + dy*dy <= sr*sr;
}

bool dfs(int i, double &l, double &r);
int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    while (cin >> n)
    {
        nodes = vector<Circle>(n);
        for (auto &c: nodes)
            cin >> c.x >> c.y >> c.r;
        G = vector<vector<int>>(n);
        for (auto i = 0; i < n; ++i)
        {
            for (auto j = 0; j < n; ++j)
            {
                if (j == i) continue;
                if (circle_overlap(nodes[i], nodes[j]))
                    G[i].push_back(j);
            }
        }

        vis = vector<int> (n);
        bool blocked = false;
        double left_y = 1000, right_y = 1000;
        for (auto i = 0; i < n; ++i)
            if (nodes[i].y + nodes[i].r >= H && !vis[i] && dfs(i, left_y, right_y))
            {
                blocked = true;
                break;
            }

        if (blocked)
            cout << "IMPOSSIBLE\n";
        else
            cout << fixed << setprecision(2) << "0.00 " << left_y << " 1000.00 " << right_y << '\n';
    }

    return 0;
}

bool dfs(int i, double &l, double &r)
{
    vis[i] = 1;
    if (nodes[i].y - nodes[i].r <= 0)
        return true;
    if (nodes[i].x <= nodes[i].r)
        l = min(l, nodes[i].y - sqrt(nodes[i].r*nodes[i].r - nodes[i].x*nodes[i].x));
    if (nodes[i].x + nodes[i].r >= H)
        r = min(r, nodes[i].y - sqrt(nodes[i].r*nodes[i].r - (1000-nodes[i].x)*(1000-nodes[i].x)));
    for (const auto next: G[i]) if (!vis[next])
        if (dfs(next, l, r))
            return true;

    return false;
}
