// Editing a book, UVa 11212

#include <cstdio>
#include <vector>
#include <list>
#include <deque>
#include <iterator>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cstring>
using namespace std;

bool dfs(const list<int> &seq, int d, int dlim);
unordered_map<int, int> vis;
// int vis[362880];
int factor[9];

void init_lookup_tab()
{
    factor[0] = 1;
    for (int i = 1; i < 9; ++i)
        factor[i] = i* factor[i-1];
}

/*int vec2int(const list<int> &v)
{
    int res = 0;
    for (auto elem: v)
    {
        res *= 10;
        res += elem;
    }

    return res;
}*/

int encode(const list<int> &v)
{
    int ret = 0;
    int i = 0;
    for (auto it = v.begin(); it != v.end(); ++it, ++i)
    {
        int cnt = 0;
        auto nit = it;
        for (++nit; nit != v.end(); ++nit)
            if (*nit < *it) cnt++;
        ret += factor[8-i] * cnt;
    }

    return ret;
}

constexpr int MAXN = 9;
int main()
{
    init_lookup_tab();
    int N, Kase = 0;
    while (scanf("%d", &N) == 1 && N)
    {
        list<int> seq(N);
        auto bit = seq.begin();
        for (auto i = 0; i < N; ++i, ++bit)
            scanf("%d", &*bit);

        int ans = 5;    // This is cheating!
        if (is_sorted(seq.begin(), seq.end()))
            ans = 0;
        else
            for (auto maxd = 1; maxd < 5; ++maxd)
            {
                vis.clear();
                // memset(vis, 0, sizeof(vis));
                if (dfs(seq, 0, maxd))
                {
                    ans = maxd;
                    break;
                }
            }
        printf("Case %d: %d\n", ++Kase, ans);
    }

    return 0;
}


bool dfs(const list<int> &seq, int d, int dlim)
{
    // list<int>::const_iterator init_iter[10];
    int boundary[10], cnt = 0, dist = 0;
    auto bit = seq.begin(), it = ++seq.begin();;
    if (*bit != 1)
    {
        boundary[cnt++] = dist;
        // init_iter[cnt] = bit;
        // cnt++;
    }
    dist++;
    for ( ; it != seq.end(); ++it, ++bit, ++dist)
        if (*it != *bit+1)
        {
            boundary[cnt++] = dist;
            // init_iter[cnt] = it;
            // cnt++;
        }
    if (*bit != seq.size())
    {
        boundary[cnt++] = dist;
        // init_iter[cnt] = it;
        // cnt++;
    }
    // Prune
    if (3*d + cnt > 3*dlim)
        return false;
    if (std::is_sorted(seq.begin(), seq.end()))
        return true;
    // Branch
    for (auto beg = 0; beg < cnt; ++beg)
    for (auto end = beg+1; end < cnt; ++end)
    {
        for (auto ins = end+1; ins < cnt; ++ins)
        {
            list<int> next(seq);
            auto bit = next.begin(), eit = next.begin(), ins_it = next.begin();
            advance(bit, boundary[beg]); advance(eit, boundary[end]); advance(ins_it, boundary[ins]);
            // auto init_bit = init_iter[beg], init_eit = init_iter[end];

            // next.erase(bit, eit);
            // next.insert(ins_it, init_bit, init_eit);
            next.splice(ins_it, next, bit, eit);

            // auto hashv = vec2int(next);
            auto &mapv = vis[encode(next)];
            if (!mapv || mapv > d)
            {
                mapv = d;
                if (dfs(next, d+1, dlim))
                    return true;
            }
        }
    }

    return false;
}

    /*vector<list<int>::iterator> boundary;
    auto bit = seq.begin();
    if (*bit != 1)
        boundary.push_back(bit);
    for (auto it = ++seq.begin(); it != seq.end(); ++it, ++bit)
        if (*it != *bit+1)
            boundary.push_back(it);
    if (*bit != seq.size())
        boundary.push_back(bit);
    // Prune
    auto separators = boundary.size();
    if (3*d + separators > 3*dlim)
        return false;
    if (std::is_sorted(seq.begin(), seq.end()))
        return true;*/
