#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    srand(std::time(0));
    if (n > 50)
        n = 50;
    for (auto j = 0; j < m; ++j)
    {
        cout << n << "\n";
        for (auto i = 0; i < n; ++i)
        {
            cout << rand()%500+1 << " "
                << rand()%500+1 << " "
                << rand()%500+1 << " "
                << rand()%500+1 << " "
                << rand()%500+1 << " "
                << rand()%500+1 << "\n";
        }
    }

    return 0;
}
