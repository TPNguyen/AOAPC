// Selling Land, ACM/ICPC NWERC 2010, UVa 12265

#include <iostream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

constexpr int MAXN = 1024;
int n, m;
char land[MAXN][MAXN];
void solve();
int main()
{
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    while (T--)
    {
        cin >> n >> m;
        for (auto i = 0; i < n; ++i)
            cin >> land[i];

        solve();
    }

    return 0;
}

void solve()
{
    vector<int> heights(m);
    map<int, int> peri2num;
    for (auto i = 0; i < n; ++i) // scan each row
    {
        for (auto j = 0; j < m; ++j)
        {
            if (land[i][j] == '#')
                heights[j] = 0;
            else
                heights[j]++;
        }

        vector<pair<int, int>> mono_st; // (c,h) pair
        for (auto j = 0; j < m; ++j)
        {
            if (heights[j] == 0)
            {
                mono_st.clear();
                continue;
            }
            if (mono_st.empty())
                mono_st.push_back({j, heights[j]});
            else
            {
                auto ch_pair = mono_st.back();
                if (heights[j] > ch_pair.second && heights[j]-j > ch_pair.second-ch_pair.first)
                    mono_st.push_back({j, heights[j]});
                else if (heights[j] < ch_pair.second)
                {
                    auto prev_ch = ch_pair;
                    while (ch_pair.second > heights[j])
                    {
                        mono_st.pop_back();
                        prev_ch = ch_pair;
                        if (!mono_st.empty())
                            ch_pair = mono_st.back();
                        else
                            break;
                    }
                    prev_ch.second = heights[j];
                    if (mono_st.empty())
                        mono_st.push_back(prev_ch);
                    else if (prev_ch.second > ch_pair.second && prev_ch.second-prev_ch.first > ch_pair.second-ch_pair.first)
                        mono_st.push_back(prev_ch);
                }
            }

            int h = mono_st.back().second, c = mono_st.back().first;
            int perimeter = 2*(j-c+1+h);
            peri2num[perimeter]++;
        }
    }

    for (auto &m: peri2num)
        cout << m.second << " x " << m.first << "\n";
}
