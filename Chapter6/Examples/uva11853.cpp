// Paintball, UVa 11853

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <iomanip>
using namespace std;

constexpr double INF = 1E6;
struct Circle {
    double x, y, r;
};

bool intersect_y(const Circle &c, double y)
{
    return abs(y-c.y) <= c.r;
}

double y_intersection(const Circle &c, double x)
{
    if (abs(c.x-x) > c.r)
        return INF;
    return c.y - sqrt(c.r*c.r - (c.x-x)*(c.x-x));
}

bool circle_overlap(const Circle &c1, const Circle &c2)
{
    return (c1.x-c2.x)*(c1.x-c2.x)+(c1.y-c2.y)*(c1.y-c2.y) <= (c1.r + c2.r)*(c1.r + c2.r);
}

bool dfs(int ind, vector<int> &vis, const vector<vector<int>> &G, const unordered_set<int> &low);
int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    while (cin >> n)
    {
        vector<Circle> nodes(n);
        for (auto &c: nodes)
            cin >> c.x >> c.y >> c.r;
        vector<vector<int>> G(n);
        unordered_set<int> intersect_upper;
        unordered_set<int> intersect_lower;
        for (auto i = 0; i < n; ++i)
        {
            if (intersect_y(nodes[i], 1000))
                intersect_upper.insert(i);
            if (intersect_y(nodes[i], 0))
                intersect_lower.insert(i);

            for (auto j = 0; j < n; ++j)
            {
                if (j == i) continue;
                if (circle_overlap(nodes[i], nodes[j]))
                    G[i].push_back(j);
            }
        }

        bool blocked = false;
        vector<int> vis (n);
        for (auto i = 0; i < n; ++i)
            if (intersect_upper.count(i) && !vis[i] && dfs(i, vis, G, intersect_lower))
            {
                blocked = true;
                break;
            }

        if (blocked)
            cout << "IMPOSSIBLE\n";
        else
        {
            // The following is wrong b/c we need to track the intersection as the circles chain together
            // Look at Version 2 in uva11853_v2.cpp
            double left_y = 1000, right_y = 1000;
            for (auto c: intersect_upper)
            {
                auto new_left_y = y_intersection(nodes[c], 0);
                auto new_right_y = y_intersection(nodes[c], 1000);
                if (new_left_y < left_y)
                    left_y = new_left_y;
                if (new_right_y < right_y)
                    right_y = new_right_y;
            }

            cout << fixed << setprecision(2) << "0.00 " << left_y << " 1000.00 " << right_y << '\n';
        }
    }

    return 0;
}

bool dfs(int ind, vector<int> &vis, const vector<vector<int>> &G, const unordered_set<int> &low)
{
    vis[ind] = 1;
    if (low.count(ind))
        return true;
    for (const auto next: G[ind]) if (!vis[next])
        if (dfs(next, vis, G, low))
            return true;

    return false;
}
