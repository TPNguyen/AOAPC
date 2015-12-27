// Shuffle, ACM/ICPC NWERC 2008, UVa 12174

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

constexpr int MAXN = 100004;
int hist[MAXN], freq[MAXN], Ok_start[MAXN], cnt1st[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    while (T--)
    {
        int s, n; cin >> s >> n;
        for (auto i = 0; i < n; ++i)
            cin >> hist[i];

        memset(freq, 0, sizeof(int)*(s+1));
        memset(Ok_start, 0, sizeof(int)*n);
        int cnt = 0, start = 0, end = 0;
        int len = std::min(s, n);
        for (; end < len; ++end)
        {
            if (++freq[hist[end]] == 1)
                cnt++;
        }
        if (cnt == len)
            Ok_start[start] = 1;

        while (end < n)
        {
            if (++freq[hist[end++]] == 1)
                cnt++;
            if (--freq[hist[start++]] == 0)
                cnt--;
            if (cnt == s)
                Ok_start[start] = 1;
        }
        while (start < n-1)
        {
            if (--freq[hist[start++]] == 0)
                cnt--;
            if (cnt == end-start)
                Ok_start[start] = 1;
        }

        memset(cnt1st, 0, sizeof(int)*(s+1));
        int valid_cnt = 0;
        for (start = 0; start < len; ++start)
        {
            if (cnt1st[hist[start]]++)
                break;

            bool valid = true;
            for (auto i = start+1; i < n; i += s)
                if (!Ok_start[i])
                {
                    valid = false;
                    break;
                }
            if (valid)
                valid_cnt ++;
        }

        if (valid_cnt == n) valid_cnt = s;
        cout << valid_cnt << "\n";
    }

    return 0;
}

