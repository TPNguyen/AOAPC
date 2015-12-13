// Division, UVa 725

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

bool has_all_digits(int d, int n);
int main()
{
    ios_base::sync_with_stdio(false);
    int N, Kase = 0;
    while (cin >> N && N)
    {
        if (Kase++) cout << "\n";
        bool has_solution = false;
        for (auto denom = max(1234, 12345/N); ; ++denom)
        {
            int numerator = denom * N;
            if (numerator > 98765) break;
            if (has_all_digits(denom, numerator))
            {
                has_solution = true;
                cout << setw(5) << numerator << " / " << setw(5) << setfill('0') << denom << " = " << N << "\n";
            }
        }
        if (!has_solution)
            cout << "There are no solutions for " << N << ".\n";
    }

    return 0;
}

bool has_all_digits(int d, int n)
{
    int vis[10] = {0};
    int count = 0;
    while (d)
    {
        if (vis[d%10])
            return false;
        vis[d%10] = 1;
        d /= 10;
        count++;
    }
    if (count < 5)
    {
        if (vis[0])
            return false;
        vis[0] = 1;
    }

    while (n)
    {
        if (vis[n%10])
            return false;
        vis[n%10] = 1;
        n /= 10;
    }

    return true;
}


