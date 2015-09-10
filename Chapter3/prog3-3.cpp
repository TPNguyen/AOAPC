#include <iostream>
#include <iomanip>
#include <array>

const int MAXN = 20;
std::array<std::array<int, MAXN>, MAXN> A{};

int main()
{
    int n, x, y, tot = 0;
    std::cin >> n;
    tot = A[x=0][y=n-1] = 1;

    while(tot < n*n)
    {
        while(x+1 < n && !A[x+1][y]) A[++x][y] = ++tot;
        while(y-1 >= 0 && !A[x][y-1]) A[x][--y] = ++tot;
        while(x-1 >= 0 && !A[x-1][y]) A[--x][y] = ++tot;
        while(y+1 < n && !A[x][y+1]) A[x][++y] = ++tot;
    }

    for (x = 0; x < n; ++x)
    {
        for (y = 0; y < n; ++y)
            std::cout << std::setw(3) << A[x][y];
        std::cout << "\n";
    }

    return 0;
}
