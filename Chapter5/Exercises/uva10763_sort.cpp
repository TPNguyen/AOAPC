// Foreign Exchange, UVa 10763

#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    while (cin >> n && n)
    {
        vector<pair<int,int>> exchange(n);
        vector<pair<int,int>> exchange_reverse(n);
        for (auto i = 0; i < n; ++i)
        {
            int s, d;
            cin >> s >> d;
            exchange[i] = make_pair(s,d);
            exchange_reverse[i] = make_pair(d,s);
        }

        sort(exchange.begin(), exchange.end());
        sort(exchange_reverse.begin(), exchange_reverse.end());
        if (exchange != exchange_reverse)
            cout << "NO\n";
        else
            cout << "YES\n";
    }

    return 0;
}


