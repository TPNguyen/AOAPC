// Lattice Animals, ACM/ICPC NEERC 2004, UVa1602

#include <iostream>
#include <vector>
#include <set>
#include <tuple>
using namespace std;

constexpr int INF = 1024;
struct cell {
    int x, y;
};
bool operator<(const cell &c0, const cell &c)
{
    if (c0.x != c.x)
        return c0.x < c.x;
    return c0.y < c.y;
}
bool operator==(const cell c0, const cell c1)
{
    return c0.x == c1.x && c0.y == c1.y;
}
bool operator!=(const cell c0, const cell c1)
{
    return !(c0 == c1);
}

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

using polyomino = set<cell>;
vector<polyomino> all_poly;

int n, w, h;

int solve();
void dfs(polyomino p);
bool is_new(polyomino &p);
polyomino normalize(polyomino &p);
polyomino rotate(polyomino &p);
polyomino reflect(polyomino &p);
pair<int, int> get_len(const polyomino &p);
bool is_within_range(const polyomino &p);

int main()
{
    while (cin >> n >> w >> h)
    {
        cout << solve() << "\n";
        all_poly.clear();
    }

    return 0;
}

int solve()
{
    polyomino p{cell{0, 0}};
    dfs(p);

    int ans = 0;
    for (const auto &p: all_poly)
    {
        if (is_within_range(p))
            ans++;
    }

    return ans;
}

pair<int, int> get_len(const polyomino &p)
{
    int minx = INF, maxx = -INF, miny = INF, maxy = -INF;
    for (const auto &c: p)
    {
        minx = min(minx, c.x), maxx = max(maxx, c.x);
        miny = min(miny, c.y), maxy = max(maxy, c.y);
    }
    return {maxx-minx, maxy-miny};
}

bool is_within_range(const polyomino &p)
{
    int xlen, ylen;
    std::tie(xlen, ylen) = get_len(p);
    if (max(xlen, ylen) < max(w, h) && min(xlen, ylen) < min(w, h))
        return true;

    return false;
}

void print_p(const polyomino &p)
{
    for (const auto &c: p)
        cout << "(" << c.x << ", " << c.y << ")";
    cout << "\n";
}

void dfs(polyomino p)
{
    if (p.size() == n)
    {
        if (is_new(p))
            all_poly.push_back(p);
        return;
    }

    for (auto &c: p)
    {
        int cx = c.x, cy = c.y;
        // generate new cells not visited
        for (auto i = 0; i < 4; ++i)
        {
            cell nc{cx+dx[i], cy+dy[i]};
            bool not_on_path;
            std::tie(std::ignore, not_on_path) = p.insert(nc);
            if (not_on_path)
            {
                if (is_within_range(p))
                    dfs(p);
                p.erase(nc);
            }
        }
    }
}

bool is_new(polyomino &p)
{
    auto np = normalize(p);
    // cout << "Testing "; print_p(np);

    for (auto i = 0; i < 4; ++i)
    {
        for (auto &poly: all_poly)
            if (poly == np)
            {
                // cout << "Conflict: "; print_p(poly);
                return false;
            }
        np = rotate(np);
    }
    np = reflect(np);
    for (auto i = 0; i < 4; ++i)
    {
        for (auto &poly: all_poly)
            if (poly == np)
            {
                // cout << "Conflict: "; print_p(poly);
                return false;
            }
        np = rotate(np);
    }

    p = np;
    // cout << "Success!!!\n";
    return true;
}

polyomino normalize(polyomino &p)
{
    int minx = p.begin()->x;
    int miny = p.begin()->y;

    polyomino ret;
    for (auto c: p)
    {
        c.x -= minx;
        c.y -= miny;
        ret.insert(c);
    }

    return ret;
}
// ccw rotate by 90 degress
polyomino rotate(polyomino &p)
{
    polyomino ret;
    for (auto c: p)
    {
        auto x = c.x, y = c.y;
        c.x = -y, c.y = x;
        ret.insert(c);
    }
    return normalize(ret);
}
// reflect along x-axis
polyomino reflect(polyomino &p)
{
    polyomino ret;
    for (auto c: p)
    {
        c.y *= -1;
        ret.insert(c);
    }
    return normalize(ret);
}
