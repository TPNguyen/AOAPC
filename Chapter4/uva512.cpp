#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <functional>

using spreadsheet = std::vector<std::vector<int>>;
const int MAX = 64;
int ColOp(spreadsheet &s, char cmd);
int RowOp(spreadsheet &s, char cmd);

void debug_output(spreadsheet &st, int r, int c)
{
    std::cout << r << ", " << c << "\n";
    for (auto i = 1; i <= r; ++i)
    {
        for (auto j = 1; j <= c; ++j)
        {
            std::cout << st[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
int main()
{
    int nr, nc, nq; // row, column, query
    int nr_orig, nc_orig;
    std::string cmd; cmd.reserve(4);
    int kase = 0;

    while (std::cin >> nr >> nc >> nq && nr)
    {
        spreadsheet st(MAX, std::vector<int>(MAX));
        std::array<std::array<int, MAX>, MAX> ans {};
        nr_orig = nr; nc_orig = nc;
        for (auto i = 1; i <= nr; ++i)
            for (auto j = 1; j <= nc; ++j)
                st[i][j] = i * 1000 + j;

        //debug_output(st, nr, nc);

        for (auto i = 0; i < nq; ++i)
        {
            std::cin >> cmd;
            if (cmd == "EX")
            {
                int r1, c1, r2, c2;
                std::cin >> r1 >> c1 >> r2 >> c2;
                std::swap(st[r1][c1], st[r2][c2]);
                nr = std::max({r1, r2, nr});
                nc = std::max({c1, c2, nc});
            }
            else
            {
                if (cmd[1] == 'R')
                    nr += RowOp(st, cmd[0]);
                else
                    nc += ColOp(st, cmd[0]);
            }

            //debug_output(st, nr, nc);
        }

        for (auto i = 1; i <= nr; ++i)
            for (auto j = 1; j <= nc; ++j)
                ans[st[i][j]/1000][st[i][j]%1000] = i*1000 + j;

        if (kase)
            std::cout << "\n";
        std::cout << "Spreadsheet #" << ++kase << "\n";
        int num_query;
        std::cin >> num_query;
        while (num_query--)
        {
            int r, c;
            std::cin >> r >> c;
            std::cout << "Cell data in (" << r << "," << c << ")";
            if (r > nr_orig || c > nc_orig)
                std::cout << " moved to (" << r << "," << c << ")\n";
            else if (ans[r][c])
                std::cout << " moved to (" << ans[r][c]/1000 << "," << ans[r][c]%1000 << ")\n";
            else
                std::cout << " GONE\n";
        }

        // for_each(std::begin(ans), std::end(ans), [](std::array<int, MAX> &arr) { arr.fill(0); });
    }

    return 0;
}

int RowOp(spreadsheet &s, char cmd)
{
    std::vector<int> sel(10);
    int numRow = 0;
    std::cin >> numRow;
    for (auto i = 0; i < numRow; ++i)
    {
        int t;
        std::cin >> t;
        sel[i] = t;
    }
    std::sort(sel.begin(), sel.begin()+numRow, std::greater<int>());

    if (cmd == 'D')
    {
        for (auto i = 0; i < numRow; ++i)
        {
            s.erase(s.begin() + sel[i]);
        }

        return -numRow;
    }
    else // if (cmd == 'I')
    {
        for (auto i = 0; i < numRow; ++i)
        {
            s.insert(s.begin() + sel[i], std::vector<int>(MAX));
        }

        return numRow;
    }
}

int ColOp(spreadsheet &s, char cmd)
{
    std::vector<int> sel(10);
    int numCol = 0;
    std::cin >> numCol;
    for (auto i = 0; i < numCol; ++i)
    {
        int t;
        std::cin >> t;
        sel[i] = t;
    }
    std::sort(sel.begin(), sel.begin()+numCol, std::greater<int>());

    if (cmd == 'D')
    {
        for (auto i = 0; i < numCol; ++i)
        {
            for_each(s.begin(), s.end(), [&sel, i] (std::vector<int> &e){ e.erase(e.begin() + sel[i]); });
        }

        return -numCol;
    }
    else // if (cmd == 'I')
    {
        for (auto i = 0; i < numCol; ++i)
        {
            for_each(s.begin(), s.end(), [&sel, i] (std::vector<int> &e){ e.insert(e.begin() + sel[i], 0); });
        }

        return numCol;
    }
}
