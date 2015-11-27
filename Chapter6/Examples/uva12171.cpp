// Sculpture, ACM/ICPC NWERC 2008, UVa12171

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>
using namespace std;

struct Box {
    int x0, y0, z0, xw, yw, zw;
};
istream & operator>> (istream& is, Box &b)
{
    return is >> b.x0 >> b.y0 >> b.z0 >> b.xw >> b.yw >> b.zw;
}

int d[][3] = {{-1, 0, 0}, {1, 0, 0},
               {0, -1, 0}, {0, 1, 0},
               {0, 0, -1}, {0, 0, 1}};

//void dfs(const vector<vector<vector<int>>> &G, vector<vector<vector<int>>> &vis, const vector<int> &xg, const vector<int> &yg, const vector<int> &zg, int z, int y, int x, int &air_v, int &air_s);

void bfs(const vector<vector<vector<int>>> &G, vector<vector<vector<int>>> &vis, const vector<int> &xg, const vector<int> &yg, const vector<int> &zg, int &air_v, int &air_s);

constexpr int maxl = 1001;
constexpr int maxv = maxl*maxl*maxl;
int main()
{
    ios_base::sync_with_stdio(false);
    int cas; cin >> cas;
    while (cas--)
    {
        int n; cin >> n;
        vector<Box> boxes(n);
        for (auto i = 0; i < n; ++i)
            cin >> boxes[i];

        vector<int> xgrids{0, maxl}; // liquid coat
        vector<int> ygrids{0, maxl};
        vector<int> zgrids{0, maxl};
        for (const auto &b: boxes)
        {
            xgrids.push_back(b.x0); xgrids.push_back(b.x0+b.xw);
            ygrids.push_back(b.y0); ygrids.push_back(b.y0+b.yw);
            zgrids.push_back(b.z0); zgrids.push_back(b.z0+b.zw);
        }
        sort(xgrids.begin(), xgrids.end());
        sort(ygrids.begin(), ygrids.end());
        sort(zgrids.begin(), zgrids.end());
        xgrids.erase(std::unique(xgrids.begin(), xgrids.end()), xgrids.end());
        ygrids.erase(std::unique(ygrids.begin(), ygrids.end()), ygrids.end());
        zgrids.erase(std::unique(zgrids.begin(), zgrids.end()), zgrids.end());

        auto xgrid_num = xgrids.size()-1;
        auto ygrid_num = ygrids.size()-1;
        auto zgrid_num = zgrids.size()-1;
        vector<vector<vector<int>>> volgraph(zgrid_num, vector<vector<int>>(ygrid_num, vector<int>(xgrid_num)));
        decltype(volgraph) vis(zgrid_num, vector<vector<int>>(ygrid_num, vector<int>(xgrid_num)));
        for (const auto &b: boxes)
        {
            auto xst = distance(xgrids.begin(), lower_bound(xgrids.begin(), xgrids.end(), b.x0));
            auto xend = distance(xgrids.begin(), lower_bound(xgrids.begin(), xgrids.end(), b.x0+b.xw));
            auto yst = distance(ygrids.begin(), lower_bound(ygrids.begin(), ygrids.end(), b.y0));
            auto yend = distance(ygrids.begin(), lower_bound(ygrids.begin(), ygrids.end(), b.y0+b.yw));
            auto zst = distance(zgrids.begin(), lower_bound(zgrids.begin(), zgrids.end(), b.z0));
            auto zend = distance(zgrids.begin(), lower_bound(zgrids.begin(), zgrids.end(), b.z0+b.zw));
            for (auto i = zst; i < zend; ++i)
                for (auto j = yst; j < yend; ++j)
                    for (auto k = xst; k < xend; ++k)
                        volgraph[i][j][k] = 1;
        }

        int air_vol = 0, air_inner_surface = 0;
        // dfs(volgraph, vis, xgrids, ygrids, zgrids, 0, 0, 0, air_vol, air_inner_surface);
        bfs(volgraph, vis, xgrids, ygrids, zgrids, air_vol, air_inner_surface);

        auto box_vol = maxv - air_vol;
        cout << air_inner_surface << " " << box_vol << "\n";
    }

    return 0;
}
void bfs(const vector<vector<vector<int>>> &G, vector<vector<vector<int>>> &vis, const vector<int> &xg, const vector<int> &yg, const vector<int> &zg, int &air_v, int &air_s)
{
    struct xyz {
        int x,y,z;
    };
    queue<xyz> Q;
    Q.push(xyz{0, 0, 0});
    vis[0][0][0] = 1;
    while (!Q.empty())
    {
        xyz C = Q.front(); Q.pop();
        auto x = C.x, y = C.y, z = C.z;
        auto zdim = zg[z+1] - zg[z];
        auto ydim = yg[y+1] - yg[y];
        auto xdim = xg[x+1] - xg[x];
        air_v += zdim * ydim * xdim;
        for (auto i = 0; i < 6; ++i)
        {
            auto nz = z + d[i][2];
            auto ny = y + d[i][1];
            auto nx = x + d[i][0];
            if (nz >= 0 && nz < zg.size()-1 && ny >= 0 && ny < yg.size()-1 && nx >=0 && nx < xg.size()-1)
            {
                if (G[nz][ny][nx] == 0) // is liquid
                {
                    if (vis[nz][ny][nx] == 0) // not visited already
                    {
                        vis[nz][ny][nx] = 1;
                        Q.push(xyz{nx, ny, nz});
                    }
                }
                else // encountered copper box
                {
                    int sa = 0;
                    if (d[i][0]) // x direction, add yz plain area
                        air_s += ydim * zdim;
                    else if (d[i][1]) // y; xz plain
                        air_s += xdim * zdim;
                    else if (d[i][2]) // z; xy plain
                        air_s += xdim * ydim;
                }
            }
        }
    }
}

/*void dfs(const vector<vector<vector<int>>> &G, vector<vector<vector<int>>> &vis, const vector<int> &xg, const vector<int> &yg, const vector<int> &zg, int z, int y, int x, int &air_v, int &air_s)
{
    vis[z][y][x] = 1;
    auto zdim = zg[z+1] - zg[z];
    auto ydim = yg[y+1] - yg[y];
    auto xdim = xg[x+1] - xg[x];
    air_v += zdim * ydim * xdim;
    for (auto i = 0; i < 6; ++i)
    {
        auto nz = z + d[i][2];
        auto ny = y + d[i][1];
        auto nx = x + d[i][0];
        if (nz >= 0 && nz < zg.size()-1 && ny >= 0 && ny < yg.size()-1 && nx >=0 && nx < xg.size()-1)
        {
            if (G[nz][ny][nx] == 0) // is liquid
            {
                if (vis[nz][ny][nx] == 0) // not visited already
                    dfs(G, vis, xg, yg, zg, nz, ny, nx, air_v, air_s);
            }
            else // encountered copper box
            {
                int sa = 0;
                if (d[i][0]) // x direction, add yz plain area
                    air_s += ydim * zdim;
                else if (d[i][1]) // y; xz plain
                    air_s += xdim * zdim;
                else if (d[i][2]) // z; xy plain
                    air_s += xdim * ydim;
            }
        }
    }
}*/
