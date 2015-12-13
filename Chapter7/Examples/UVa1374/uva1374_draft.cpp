// Power Calculus, ACM/ICPC Yokohama 2006, UVa 1374

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cassert>
using namespace std;

constexpr int INF = 1025;
int N;
bool found;
int st[16];
int vis[INF];

void dfs_search(int d, int lim);
int heur(int num)
{
    // if (binary_search(st.begin(), st.begin()+num, N))
    int max = 0;
    for (auto i = 0; i < num; ++i)
    {
        if (st[i] == N)
            return 0;
        if (st[i] > max)
            max = st[i];
    }
    auto ans = log2(N/max);
    return ans > 0 ? std::ceil(ans) : 1;
}
int main()
{
    ios_base::sync_with_stdio(false);
    while (cin >> N && N)
    {
        memset(vis, 0, sizeof(vis));
        st[0] = 1;
        vis[0] = vis[1] = 1;
        found = false;
        int bound = std::ceil(log2(N));
        for (; !found; ++bound)
            dfs_search(0, bound);
    }

    return 0;
}

void dfs_search(int d, int lim)
{
    /*for (auto i = 0; i <= d; ++i)
        cout << st[i] << ", ";
    cout << endl;*/
    /*int h = heur(d+1);
    if (d + h > lim)    return ;
    if (h == 0) // d == lim
    {
        found = true;
        cout << d << endl;
        return;
    }*/

    if (st[d] == N)
    {
        found = true;
        cout << d << "\n";
        return;
    }

    if ((st[d] << (lim-d)) < N)
        return;

    // int min_bound = INF;
    // int t;
    for (int i = d; i >= 0; --i)
    {
        // for (int j = i; j >= 0; --j)
        {
            // int st_copy[INF]; memcpy(st_copy, st, sizeof(st));
            st[d+1] = st[d]+st[i];
            // int num_bigger = std::count_if(st, st+d+1+1, [](int a){ return a > N;});
            if (st[d+1] <= 1024 && !vis[st[d+1]])
            {
                vis[st[d+1]] = 1;
                dfs_search(d+1, lim);
                if (found) return ;
                vis[st[d+1]] = 0;
                // memcpy(st, st_copy, sizeof(st_copy));
            }

            st[d+1] = std::abs(st[d]-st[i]);
            // num_bigger = std::count_if(st, st+d+1+1, [](int a){ return a > N;});
            if (st[d+1] <= 1024 && !vis[st[d+1]])// && !(st[d] > N && st[d+1] > N))
            {
                vis[st[d+1]] = 1;
                dfs_search(d+1, lim);
                if (found) return ;
                vis[st[d+1]] = 0;
            }
            // memcpy(st, st_copy, sizeof(st_copy));
        }
        /*for (int j = 0; j < i; ++j)
        {
            int st_copy[INF]; memcpy(st_copy, st, sizeof(st));
            st[d+1] = st[i]+st[j];
            if (st[d] > N && st[d+1] > N)
                continue;
            t = dfs_search(d+1, lim);
            if (found) return 0;
            memcpy(st, st_copy, sizeof(st_copy));
        }*/
    }
}
            /*sort(st_next.begin(), st_next.end());
            st_next.erase(std::unique(st_next.begin(), st_next.end()), st_next.end());
            min_bound = min(min_bound, t);
            if (st[d+1] > 2048)
            {
                cout << "Error: " << st[d+1] <<". lim = " << lim << "; d = " << d << "; h = " << h << endl;
                assert(st[d+1] <= 2048);
            }*/
