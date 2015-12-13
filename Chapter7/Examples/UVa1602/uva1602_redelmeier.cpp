// Lattice Animals, ACM/ICPC NEERC 2004, UVa1602

#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>
#include <stack>
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

using polyomino = vector<cell>;
using untried = stack<cell>;
using cell_set = set<cell>;
set<polyomino> all_poly;
int n, w, h;
// down, left, up, right
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};
cell_set all_untried;
static int fixed_count;

// functions
int solve();
void dfs(polyomino &p, untried uts);
bool is_new(polyomino &p);
void normalize(polyomino &p);
void rotate(polyomino &p);
void reflect(polyomino &p);
pair<int, int> get_len(const polyomino &p);
bool is_within_range(const polyomino &p);
void print_p(const polyomino &p);

int main()
{
    while (cin >> n >> w >> h)
    {
        cout << solve() << "\n";
        all_poly.clear();
        // all_untried.clear();
        fixed_count = 0;
    }

    return 0;
}

int solve()
{
    polyomino p;
    untried uts; uts.push(cell{0, 0});
    all_untried.insert(cell{0,0});

    dfs(p, uts);

    /*int ans = 0;
    for (const auto &po: all_poly)
        if (is_within_range(po))
            ans++;*/

    return all_poly.size();
}

void dfs(polyomino &p, untried uts) // uts = untried-set
{
    while (!uts.empty())  // step 0
    {
        p.push_back(uts.top()); uts.pop(); // step 1 & 2
        if (is_within_range(p)) {
        if (p.size() == n)      // step 3
        {
            // cout << "fixed# " << ++fixed_count << "\n";
            // print_p(p);
            auto p_copy = p;
            if (is_new(p_copy))
            {
                // cout << "Save: "; print_p(p_copy);
                all_poly.insert(std::move(p_copy));
            }
        }
        else {                  // step 4
            // generate new neighbours cells not visited // step 4(a)
            auto c = p.back();
            int cx = c.x, cy = c.y;
            auto new_neigb_count = 0;
            for (auto i = 0; i < 4; ++i)
            {
                cell nc{cx+dx[i], cy+dy[i]};
                if (nc.y < 0 || (nc.x < 0 && nc.y == 0))
                    continue;
                else
                {
                    if (all_untried.insert(nc).second)
                    {
                        uts.push(nc);
                        new_neigb_count++;
                    }
                }
            }
            dfs(p, uts);                                // step 4(b)
            while (new_neigb_count--)                   // step 4(c)
            {
                auto pp = uts.top();
                // untried points only include points not used by ancestors and ancestors' old brothers
                // those points are only in current stack.
                all_untried.erase(pp);
                uts.pop();
            }
        }
        }
        p.pop_back();       // step 5
    }
}

bool is_new(polyomino &p)
{
    // cout << "Testing "; print_p(p);

    for (auto i = 0; i < 4; ++i)
    {
        rotate(p);
        if (all_poly.count(p))
            return false;
        /*for (auto &poly: all_poly)
            if (poly == p)
            {
                // cout << "Conflict: "; print_p(poly);
                return false;
            }*/
    }
    reflect(p);
    for (auto i = 0; i < 4; ++i)
    {
        rotate(p);
        if (all_poly.count(p))
            return false;
        /*for (auto &poly: all_poly)
            if (poly == p)
            {
                // cout << "Conflict: "; print_p(poly);
                return false;
            }*/
    }

    // cout << "Success!!!\n";
    return true;
}

void normalize(polyomino &p)
{
    int minx = p.begin()->x;
    int miny = p.begin()->y;

    for (auto &c: p) {
        minx = min(minx, c.x);
        miny = min(miny, c.y);
    }

    for (auto &c: p) {
        c.x -= minx;
        c.y -= miny;
    }
    sort(p.begin(), p.end());
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

void print_p(const polyomino &p)
{
    for (const auto &c: p)
        cout << "(" << c.x << ", " << c.y << ")";
    cout << "\n";
}

pair<int, int> get_len(const polyomino &p)
{
    int minx = INF, maxx = -INF, miny = INF, maxy = -INF;
    for (const auto &c : p)
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

