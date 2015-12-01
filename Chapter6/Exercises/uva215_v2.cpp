// Spreadsheet Calculator, ACM/ICPC World Finals 1992, UVa 215

#include <iostream>
#include <utility>
#include <string>
#include <tuple>
#include <cstring>
#include <iomanip>
using namespace std;

constexpr int MAXR = 24;
constexpr int MAXC = 12;
string SS[MAXR][MAXC];
int Res[MAXR][MAXC];
int vis[MAXR][MAXC];
int R, C;

pair<int, bool> dfs(int r, int c);
bool topological_sort();
int main()
{
    while (cin >> R >> C && R)
    {
        for (auto i = 0; i < R; ++i)
            for (auto j = 0; j < C; ++j)
                cin >> SS[i][j];

        if(topological_sort())
        {
            for (auto i = 0; i < R; ++i)
                for (auto j = 0; j < C; ++j)
                {
                    if (vis[i][j] == -1)
                        cout << (static_cast<unsigned char>('A'+i)) << (static_cast<unsigned char>('0'+j)) << ": " << SS[i][j] << "\n";
                }
        }
        else
        {
            cout << " ";
            for (auto j = 0; j < C; ++j)
                cout << setw(6) << j;
            cout << "\n";
            for (auto i = 0; i < R; ++i)
            {
                cout << (static_cast<unsigned char>('A'+i));
                for (auto j = 0; j < C; ++j)
                {
                    cout << setw(6) << Res[i][j];
                }
                cout << "\n";
            }
        }
        cout << "\n";

        // reset global data
        memset(vis, 0, sizeof(vis));
        memset(Res, 0, sizeof(Res));
    }

    return 0;
}

pair<int, bool> dfs(int r, int c)
{
    vis[r][c] = -1; // visiting
    bool cycle_found = false;
    // if (isalpha(static_cast<unsigned char>(SS[r][c][0]))) // cell is expression
    {
        int ind = 0, val = 0;
        int temp;
        bool is_add = true;
        while (ind < SS[r][c].size())
        {
            if (isalpha(static_cast<unsigned char>(SS[r][c][ind])))
            {
                int row = SS[r][c][ind++] - 'A';
                int col = SS[r][c][ind++] - '0';
                if (vis[row][col] == -1) // cycle found
                {
                    cycle_found = true;
                    break;
                }
                if (vis[row][col] == 0)
                {
                    std::tie(temp, cycle_found) = dfs(row, col);
                    if (cycle_found) break;
                }
                else
                    temp = Res[row][col];
                if (is_add)
                    val += temp;
                else
                    val -= temp;
            }
            else if (SS[r][c][ind] == '+')
            {
                is_add = true;
                ++ind;
            }
            else if (SS[r][c][ind] == '-')
            {
                is_add = false;
                ++ind;
            }
            else // number
            {
                auto nlast = SS[r][c].find_first_not_of("0123456789", ind);
                temp = stoi(SS[r][c].substr(ind, nlast-ind));
                ind = nlast;
                if (is_add)
                    val += temp;
                else
                    val -= temp;
            }
        }
        Res[r][c] = val;
    }

    if (!cycle_found)
        vis[r][c] = 1;
    return  {Res[r][c], cycle_found};
}



bool topological_sort()
{
    bool has_cycle = false;
    for (auto i = 0; i < R; ++i)
        for (auto j = 0; j < C; ++j) if (!vis[i][j])
        {
            bool this_has_cycle;
            std::tie(std::ignore, this_has_cycle) = dfs(i, j);
            if (this_has_cycle)
                has_cycle = true;
        }

    return has_cycle;
}

