// A Dicey Problem, ACM/ICPC World Finals 1999, UVa 810
// http://morris821028.github.io/2014/12/27/uva-810/
// http://blog.csdn.net/acm_hkbu/article/details/41822851
// http://blog.csdn.net/wcr1996/article/details/43292121
// http://www.cnblogs.com/Bowen-/p/4935750.html ( vis doesn't need to be reset to 0.)
// http://www.cnblogs.com/20143605--pcx/p/4863560.html (have no idea what left/right array means)
// http://www.cnblogs.com/jerryRey/p/4644268.html
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cstring>
using namespace std;

constexpr int MAXR = 16;
constexpr int MAXC = 16;
int board[MAXR][MAXC];
int R, C, sR, sC;

int vis[MAXR][MAXC][7][7];
// up, down, left, right
int disp[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
// Given top and front, give the right face
int dright[7][7] = { 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 3, 5, 2, 4, 0,
                     0, 4, 0, 1, 6, 0, 3,
                     0, 2, 6, 0, 0, 1, 5,
                     0, 5, 1, 0, 0, 6, 2,
                     0, 3, 0, 6, 1, 0, 4,
                     0, 0, 4, 2, 5, 3, 0,};

vector<pair<int, int>> paths;
void rotate(int tp, int ft, int d, int &ntp, int &nft)
{
    switch(d)
    {
        case 0:
            ntp = ft; nft = 7 - tp;
            break;
        case 1:
            ntp = 7-ft; nft = tp;
            break;
        case 2:
            ntp = dright[tp][ft]; nft = ft;
            break;
        case 3:
            ntp = 7-dright[tp][ft]; nft = ft;
            break;
    }
}
bool dfs(int sr, int sc, int tp, int fnt);
void print_path();

int main()
{
    ios_base::sync_with_stdio(false);
    string name;
    while (cin >> name && name != "END")
    {
        cout << name << "\n";
        int top, front;
        cin >> R >> C >> sR >> sC >> top >> front;
        for (auto i = 1; i <= R; ++i)
            for (auto j = 1; j <= C; ++j)
                cin >> board[i][j];

        if (dfs(sR, sC, top, front))
            print_path();
        else
            cout << "  No Solution Possible\n";

        paths.clear();
        memset(vis, 0, sizeof(vis));
    }

    return 0;
}

bool dfs(int sr, int sc, int tp, int fnt)
{
    vis[sr][sc][tp][fnt] = 1;
    paths.push_back({sr, sc});
    // unlike usual way of dfs, I am going to try stepping out first and test if goal is reached there
    for (auto i = 0; i < 4; ++i)
    {
        auto newsr = sr + disp[i][0], newsc = sc + disp[i][1];
        // test if it can be stepped
        if (newsr < 1 || newsr > R || newsc < 1 || newsc > C) // outside
            continue;
        if (board[newsr][newsc] != -1 && board[newsr][newsc] != tp) // pattern do not match
            continue;
        // only check if back to initial position after checking pattern match
        if (newsr == sR && newsc == sC)
            return true;
        int ntp, nfnt;
        rotate(tp, fnt, i, ntp, nfnt);
        if (vis[newsr][newsc][ntp][nfnt]) // new config encountered before
            continue;

        if (dfs(newsr, newsc, ntp, nfnt))
            return true;
    }

    paths.pop_back();
    return false;
}

void print_path()
{
    paths.push_back({sR, sC});
    auto tot = paths.size();
    for (auto i = 0; i < tot; ++i)
    {
        if (i % 9 == 0)
        {
            if (i) cout << ",\n";
            cout << "  (" << paths[i].first << "," << paths[i].second << ")";
        }
        else
            cout << ",(" << paths[i].first << "," << paths[i].second << ")";
    }
    cout << "\n";
}
