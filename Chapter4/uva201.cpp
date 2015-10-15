// Squares, ACM/ICPC World Finals 1990, Uva201

#include <iostream>
#include <bitset>
#include <cstring>

using namespace std;

constexpr int MAXN = 10;

bool is_square(int, int, int, const bitset<2> (&)[MAXN][MAXN]);
int main()
{
    bitset<2> board[MAXN][MAXN]; // first bit indicate horizontal segment; second bit vertical
    int Kase = 0;
    int m, n;
    while (cin >> n >> m && n >= 2)
    {
        for (auto i = 0; i < m; ++i)
        {
            char c; int start, offset;
            cin >> c >> start >> offset;
            if (c == 'H')
                board[start][offset].set(0);
            else if (c == 'V')
                board[offset][start].set(1);
        }

        int counts[MAXN] = {0};
        bool has_complete_square = false;
        for (auto len = 1; len < n; ++len)
        {
            for (auto si = 1; si + len <= n; ++si)
                for (auto sj = 1; sj + len <= n; ++sj)
                {
                    if (is_square(si, sj, len, board))
                    {
                        has_complete_square = true;
                        ++counts[len];
                    }
                }
        }

        if (Kase > 0)
            cout << "\n**********************************\n\n";
        cout << "Problem #" << ++Kase << "\n\n";
        if (has_complete_square)
        {
            for (auto i = 1; i < n; ++i)
            {
                if (counts[i])
                    cout << counts[i] << " square (s) of size " << i << "\n";
            }
        }
        else
            cout << "No completed squares can be found.\n";

        memset(&board, 0, sizeof(board));
    }

    return 0;
}

bool is_square(int si, int sj, int len, const bitset<2> (&g)[MAXN][MAXN])
{
    // test square's top segment
    for (auto i = 0; i < len; ++i)
        if (!g[si][sj+i].test(0))
            return false;

    // test square's left segment
    for (auto i = 0; i < len; ++i)
        if (!g[si+i][sj].test(1))
            return false;

    // test square's right segment
    for (auto i = 0; i < len; ++i)
        if (!g[si+i][sj+len].test(1))
            return false;

    // test square's bottom segment
    for (auto i = 0; i < len; ++i)
        if (!g[si+len][sj+i].test(0))
            return false;

    return true;
}


