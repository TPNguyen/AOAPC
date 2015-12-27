// Shuffle, ACM/ICPC NWERC 2008, UVa 12174

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    while (T--)
    {
        int s, n; cin >> s >> n;
        vector<int> hist(n);
        for (auto i = 0; i < n; ++i)
            cin >> hist[i];

        vector<int> freq(s+1);
        vector<int> Ok_start(n);
        int cnt = 0, start = 0, end = 0;
        for (; end < min(s, n); ++end)
        {
            if (++freq[hist[end]] == 1)
                cnt++;
        }
        if (cnt == end-start)
            Ok_start[start] = 1;

        while (end < n)
        {
            if (++freq[hist[end++]] == 1)
                cnt++;
            if (--freq[hist[start++]] == 0)
                cnt--;
            if (cnt == end-start)
                Ok_start[start] = 1;
        }
        while (start < n-1)
        {
            if (--freq[hist[start++]] == 0)
                cnt--;
            if (cnt == end-start)
                Ok_start[start] = 1;
        }

        vector<int> cnt1st(s+1);
        int valid_cnt = 0;
        for (start = 0; start < min(s,n); ++start)
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

        if (n < s && valid_cnt == n) valid_cnt = s;
        cout << valid_cnt << "\n";
    }

    return 0;
}
