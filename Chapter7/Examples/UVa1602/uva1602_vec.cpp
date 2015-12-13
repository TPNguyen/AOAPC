// Lattice Animals, ACM/ICPC NEERC 2004, UVa1602

#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>
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

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

using polyomino = vector<cell>;
vector<polyomino> all_poly;

int n, w, h;

int solve();
void dfs(polyomino &p, int);
bool is_new(polyomino &p);
void normalize(polyomino &p);
void rotate(polyomino &p);
void reflect(polyomino &p);
pair<int, int> get_len(const polyomino &p, int);
bool is_within_range(const polyomino &p, int);

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
    polyomino p(n);
    p[0] = cell{0, 0};

    dfs(p, 1);

    return all_poly.size();
}

pair<int, int> get_len(const polyomino &p, int len)
{
    int minx = INF, maxx = -INF, miny = INF, maxy = -INF;
    for (auto i = 0; i < len; ++i)
    {
        auto c = p[i];
        minx = min(minx, c.x), maxx = max(maxx, c.x);
        miny = min(miny, c.y), maxy = max(maxy, c.y);
    }
    return {maxx-minx, maxy-miny};
}

bool is_within_range(const polyomino &p, int len)
{
    int xlen, ylen;
    std::tie(xlen, ylen) = get_len(p, len);
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

void dfs(polyomino &p, int level)
{
    if (level == n)
    {
        auto p_copy = p;
        if (is_new(p_copy))
        {
            // cout << "Save: "; print_p(p_copy);
            all_poly.push_back(std::move(p_copy));
            cout << "# " <<  all_poly.size() << "\n";
        }
        return;
    }

    for (auto ci = 0; ci < level; ++ci)
    {
        auto c = p[ci];
        int cx = c.x, cy = c.y;
        // generate new cells not visited
        for (auto i = 0; i < 4; ++i)
        {
            cell nc{cx+dx[i], cy+dy[i]};
            if (find(p.begin(), p.begin()+level, nc) == p.begin()+level)
            {
                p[level] = nc;
                if (is_within_range(p, level+1))
                    dfs(p, level+1);
            }
        }
    }
}

bool is_new(polyomino &p)
{
    // cout << "Testing "; print_p(p);

    for (auto i = 0; i < 4; ++i)
    {
        rotate(p);
        // print_p(p);
        for (auto &poly: all_poly)
            if (poly == p)
            {
                // cout << "Conflict: "; print_p(poly);
                return false;
            }
    }
    reflect(p);
    // print_p(p);
    for (auto i = 0; i < 4; ++i)
    {
        rotate(p);
        // print_p(p);
        for (auto &poly: all_poly)
            if (poly == p)
            {
                // cout << "Conflict: "; print_p(poly);
                return false;
            }
    }

    // cout << "Success!!!\n";
    return true;
}

void normalize(polyomino &p)
{
    sort(p.begin(), p.end());
    int firstx = p.begin()->x;
    int firsty = p.begin()->y;

    for (auto &c: p)
    {
        c.x -= firstx;
        c.y -= firsty;
    }
}
// ccw rotate by 90 degress
void rotate(polyomino &p)
{
    for (auto &c: p)
    {
        auto x = c.x, y = c.y;
        c.x = -y, c.y = x;
    }
    normalize(p);
}
// reflect along x-axis
void reflect(polyomino &p)
{
    for (auto &c: p)
    {
        c.y *= -1;
    }
    normalize(p);
}

