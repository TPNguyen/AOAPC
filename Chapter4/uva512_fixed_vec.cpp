#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <functional>

const int MAX = 64;
using spreadsheet = std::vector<std::vector<int>>;
// using spreadsheet = std::array<<std::array<int>, MAX>, MAX>;
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

// declare global variables
int nr, nc, nm; // row, column, manipulation

int main()
{
    std::string cmd; cmd.reserve(4);
    int kase = 0;
    int nr_orig, nc_orig;
    spreadsheet st(MAX, std::vector<int> (MAX)), ans(MAX, std::vector<int> (MAX));

    while (std::cin >> nr >> nc >> nm && nr)
    {
        nr_orig = nr; nc_orig = nc;
        for (auto i = 1; i <= nr; ++i)
            for (auto j = 1; j <= nc; ++j)
                st[i][j] = i * 1000 + j;

        // debug_output(st, nr, nc);

        for (auto i = 0; i < nm; ++i)
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

            // debug_output(st, nr, nc);
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
        for_each(ans.begin()+1, ans.begin()+1+nr, [](std::vector<int> &arr) { std::fill(arr.begin()+1, arr.begin()+1+nc, 0); });
        for_each(st.begin()+1, st.begin()+1+nr, [](std::vector<int> &arr) { std::fill(arr.begin()+1, arr.begin()+1+nc, 0); });
    }

    return 0;
}

int RowOp(spreadsheet &s, char cmd)
{
    std::vector<int> sel(MAX);
    int numRow = 0;
    int numRowInRange = 0;
    std::cin >> numRow;
    for (auto i = 0; i < numRow; ++i)
    {
        int t;
        std::cin >> t;
        if (t <= nr)
        {
            sel[t] = 1;
            ++numRowInRange;
        }
    }

    if (cmd == 'D')
    {
        for (auto i = 1, j = 1; j <= nr; ++j)
        {
            if (!sel[j])
            {
                if(j != i)
                    std::swap(s[i], s[j]);
                ++i;
            }
            else
                std::fill(s[j].begin(), s[j].end(), 0);

        }

        return -numRowInRange;
    }
    else // if (cmd == 'I')
    {
        for (auto i = numRowInRange, j = nr; i > 0 && j > 0; --j)
        {
            std::swap(s[j+i], s[j]);
            if (sel[j])
                --i;
        }

        return numRowInRange;
    }
}

int ColOp(spreadsheet &s, char cmd)
{
    std::vector<int> sel(12);
    int numCol = 0;
    int numColInRange = 0;
    std::cin >> numCol;
    for (auto i = 0; i < numCol; ++i)
    {
        int t;
        std::cin >> t;
        if (t <= nc)
        {
            sel[numColInRange++] = t;
        }
    }
    std::sort(sel.begin(), sel.begin()+numColInRange);
    sel[numColInRange] = nc + 1;

    if (cmd == 'D')
    {
        for (auto i = 1; i <= numColInRange; ++i)
        {
            if (sel[i-1]+1 < sel[i])
            for_each(s.begin()+1, s.begin()+nr+1,
                        [&sel, i] (std::vector<int> &e)
                        {
                            std::copy(e.begin()+sel[i-1]+1, e.begin()+sel[i], e.begin()+sel[i-1]+1-i);
                        }
                    );
        }

        return -numColInRange;
    }
    else // if (cmd == 'I')
    {
        for (auto i = numColInRange; i > 0; --i)
        {
            for_each(s.begin()+1, s.begin()+nr+1,
                        [&sel, i] (std::vector<int> &e)
                        {
                            std::copy_backward(e.begin()+sel[i-1], e.begin()+sel[i], e.begin()+sel[i]+i);
                            e[sel[i-1]+i-1] = 0;
                        }
                    );
        }

        return numColInRange;
    }
}
