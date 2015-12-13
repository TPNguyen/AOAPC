// Square Destroyer, ACM/ICPC Taejon 2001, UVa 1603

// at most there are 2*5*(5+1) = 60 matchsticks
// at most there are 5*5+4*4+...+1*1 = 55 squares

#include <iostream>
#include <bitset>
using namespace std;

bitset<63> squares[56];
bitset<63> allMatch;
int n, k, si;
bool found;

inline int totalMatch()
{
    return 2*n*(n+1);
}
inline int getRowMatch(int x, int y)
{
    return (2*n+1)*x + y;
}
inline int getColMatch(int x, int y)
{
    return (2*n+1)*x+n+y;
}
void init();
int find_complete_square();
int solve(int depth, int dlimit);

int main()
{
    int T; cin >> T;
    while (T--)
    {
        init();
        int depth_limit = 0;
        while (!found)
            depth_limit = solve(0, depth_limit);
        cout << depth_limit << "\n";
    }

    return 0;
}

void init()
{
    cin >> n >> k;
    si = 0;
    found = false;
    allMatch.set();
    for (auto slen = 1; slen <= n; ++slen)
        for (auto xi = 0; xi <= n-slen; ++xi) // top left x index
            for (auto yi = 0; yi <= n-slen; ++yi) // top left y index
            {
                squares[si].reset();
                for (auto li = 0; li < slen; ++li)
                {
                    auto up = getRowMatch(xi, yi+li);
                    auto down = getRowMatch(xi+slen, yi+li);
                    auto left = getColMatch(xi+li, yi);
                    auto right = getColMatch(xi+li, yi+slen);
                    squares[si].set(up);
                    squares[si].set(down);
                    squares[si].set(left);
                    squares[si].set(right);
                }
                si++;
            }

    while (k--)
    {
        int rem; cin >> rem;
        allMatch.reset(rem-1);
    }
}

int find_complete_square()
{
    for (auto i = 0; i < si; ++i)
        if ((allMatch & squares[i]) == squares[i])
            return i;
    return -1;
}

int solve(int depth, int dlimit)
{
    int next_square = find_complete_square();
    if (next_square == -1)
    {
        found = true;
        return dlimit;
    }
    if (depth >= dlimit)
        return dlimit+1;


    for (auto i = totalMatch()-1; i >= 0; --i)
    {
        if (squares[next_square].test(i))
        {
            allMatch.reset(i);
            solve(depth+1, dlimit);
            if (found)
                return dlimit;
            allMatch.set(i);
        }
    }
}

