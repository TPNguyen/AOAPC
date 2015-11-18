// Foreign Exchange, UVa 10763

#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    while (cin >> n && n)
    {
        // unordered_map<long long, int> exchange;
        map<pair<int,int>, int> exchange;
        for (auto i = 0; i < n; ++i)
        {
            int s, d;
            cin >> s >> d;
            int val = 1;
            if (s > d)
            {
                val = -1;
                swap(s, d);
            }
            // long long key = s*500001 + d;
            auto p = exchange.insert({{s,d}, val});
            if (p.second == false)
                // exchange[key] += val;
                p.first->second += val;
        }

        bool matched = true;
        for (const auto &kv: exchange)
            if (kv.second != 0)
            {
                matched = false;
                break;
            }

        if (matched)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}

