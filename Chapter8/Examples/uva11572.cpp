// Unique snowflakes, UVa 11572

#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

constexpr int MAXN = 1000004;
int sizes[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    int N; cin >> N;
    while (N--)
    {
        int num; cin >> num;
        for (auto i = 0; i < num; ++i)
            cin >> sizes[i];

        int longest_window = 0;
        int cur_window_end = 0;
        int cur_window_start = 0;
        unordered_map<int, int> size2index;

        for (auto i = 0; i < num; ++i)
        {
            auto ires = size2index.insert({sizes[i], i});
            if (ires.second)
                ;
            else if (ires.first->second < cur_window_start)
                ires.first->second = i;
            else
            {
                longest_window = max(longest_window, cur_window_end-cur_window_start);
                cur_window_start = ires.first->second + 1;
                ires.first->second = i;
            }
            cur_window_end++;
        }

        longest_window = max(longest_window, cur_window_end-cur_window_start);

        cout << longest_window << '\n';
    }

    return 0;
}
