// Copying books, UVa714

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;
constexpr int MAXN = 512;
int pms[MAXN];
int m, k;

bool can_achieve(ll pages);
int main()
{
    ios_base::sync_with_stdio(false);
    int N; cin >> N;
    while (N--)
    {
        cin >> m >> k;
        for (auto i = 0; i < m; ++i)
            cin >> pms[i];

        ll M = 0; M = std::accumulate(pms, pms+m, M);
        ll lo = *std::max_element(pms, pms+m);

        while (lo < M)
        {
            ll mid = lo + (M-lo)/2;
            if (can_achieve(mid))
                M = mid;
            else
                lo = mid+1;
        }
        // Lo is the answer

        vector<int> ans;
        ll page_count = 0;
        k--;
        for (auto i = m-1; i >= 0; --i)
        {
            if (page_count + pms[i] <= lo && i >= k)
            {
                ans.push_back(pms[i]);
                page_count += pms[i];
            }
            else
            {
                ans.push_back(-1);
                ans.push_back(pms[i]);
                page_count = pms[i];
                k--;
            }
        }

        for (auto i = ans.size()-1; i > 0; --i)
        {
            if (ans[i] == -1)
                cout << "/ ";
            else
                cout << ans[i] << " ";
        }
        cout << ans[0] << "\n";
    }


    return 0;
}

bool can_achieve(ll pages)
{
    int scriber_count = 1;
    ll page_count = 0;
    for (auto i = 0; i < m; ++i)
    {
        // if (pms[i] > pages) return false;
        page_count += pms[i];
        if (page_count > pages)
        {
            scriber_count ++;
            page_count = pms[i];
        }
    }

    return scriber_count <= k;
}
