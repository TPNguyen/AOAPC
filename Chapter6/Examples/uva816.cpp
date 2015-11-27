// Abbott's Revenge, ACM/ICPC World Finals 2000, UVa 816

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
using namespace std;

constexpr int MAXMD = 10;
constexpr int MAXDIR = 4;
constexpr int MAXTURN = 3;
const char dir[] = "NWSE"; // traveling
const char sign[] = "LFR";
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, -1, 0, 1};
struct Node {
    int r, c, d;
};

// using MAZE = vector<char> [MAXMD][MAXMD][MAXDIR];
typedef int Maze[MAXMD][MAXMD][MAXDIR][MAXDIR];

inline int dir_id(char c) { return strchr(dir, c) - dir; }
inline int get_dir(int d, char turn)
{
    if (turn == 'L')
        return (d+1) % 4;
    if (turn == 'R')
        return (d+3) % 4;
    return d;
}

inline Node next(int r, int c, int d)
{
    return Node{r+dr[d], c+dc[d], d};
}

void read_maze(Maze& mz)
{
    int r, c;
    while (cin >> r && r)
    {
        cin >> c;
        string grp;
        while (cin >> grp && grp != "*")
        {
            int d = dir_id(grp[0]);
            for (auto i = 1; i < grp.size(); ++i)
                mz[r][c][d][get_dir(d, grp[i])] = 1;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    string mazeid;
    while (cin >> mazeid && mazeid != "END")
    {
        bool vis[MAXMD][MAXMD][MAXDIR]  {};
        Node fa[MAXMD][MAXMD][MAXDIR];

        int r0, c0, r, c;
        char d0;
        cin >> r0 >> c0 >> d0 >> r >> c;
        Node first = next(r0, c0, dir_id(d0));
        fa[first.r][first.c][first.d] = {r0, c0, -1};

        Maze maze {};
        read_maze(maze);

        bool found = false;
        vector<Node> paths;
        queue<Node> Q;
        Q.push(first);
        while (!Q.empty())
        {
            Node u = Q.front();
            if (u.r == r && u.c == c)
            {
                found = true;
                paths.push_back(u);
                break;
            }
            Q.pop();
            vis[u.r][u.c][u.d] = true;
            for (auto i = 0; i < MAXDIR; ++i)
            {
                if (maze[u.r][u.c][u.d][i])
                {
                    Node v = next(u.r, u.c, i);
                    if (!vis[v.r][v.c][v.d])
                    {
                        fa[v.r][v.c][v.d] = {u.r, u.c, u.d};
                        Q.push(v);
                    }
                }
            }
        }

        cout << mazeid << "\n";
        if (!found)
            cout << "  No Solution Possible\n";
        else {
            for (auto p = paths.back(); p.r != r0 || p.c != c0 || p.d != -1; p = paths.back())
                paths.push_back(fa[p.r][p.c][p.d]);

            int cnt = 0;
            for (int i = paths.size()-1; i >= 0; --i)
            {
                if (cnt % 10 == 0) cout << " ";
                cout << " (" << paths[i].r << "," << paths[i].c << ")";
                if (++cnt % 10 == 0) cout << "\n";
            }
            if (paths.size() % 10 != 0)
                cout << "\n";
        }
    }

    return 0;
}
