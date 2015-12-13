// Editing a book, UVa 11212

#include <cstdio>
#include <vector>
#include <deque>
#include <iterator>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int N;
vector<int> seq(9);

bool dfs(int d, int dlim);
unordered_map<int, int> vis;

int vec2int()
{
    int res = 0;
    for (auto i = 0; i < N; ++i)
    {
        res *= 10;
        res += seq[i];
    }

    return res;
}
int main()
{
    int Kase = 0;
    while (scanf("%d", &N) == 1 && N)
    {
        for (auto i = 0; i < N; ++i)
            scanf("%d", &seq[i]);

        for (auto maxd = 0; maxd <= 5; ++maxd)
        {
            if (maxd == 5 || dfs(0, maxd))
            {
                printf("Case %d: %d\n", ++Kase, maxd);
                break;
            }
            vis.clear();
        }
    }

    return 0;
}


bool dfs(int d, int dlim)
{
    /*printf("cur_dep = %d; depth limit = %d;\n", d, dlim);
    for (auto ele: seq)
        printf("%d ", ele);
    printf("\n");*/
    if (d == dlim)
    {
        if (std::is_sorted(seq.begin(), seq.begin()+N))
            return true;
        else
            return false;
    }

    deque<int> boundary;
    for (auto i = 1; i < N; ++i)
        if (seq[i] != seq[i-1]+1)
            boundary.push_back(i);
    // Prune
    auto separators = boundary.size();
    if (3*d + separators > 3*dlim)
        return false;

    boundary.push_front(0); boundary.push_back(N);
    // Branch
    for (auto cons = 1; cons <= (separators+1)/2; ++cons)
    for (auto i = 0; i < boundary.size()-cons; ++i)
    {
        auto bit = boundary[i], eit = boundary[i+cons];
        for (auto ins = 0; ins < boundary.size(); ++ins)
        {
            auto ins_it = boundary[ins];
            if (bit <= ins_it && eit >= ins_it)
                continue;

            vector<int> next(seq);
            std::copy(seq.begin()+bit, seq.begin()+eit, inserter(next, next.begin()+ins_it));
            int  len = 0;
            if (ins_it < bit)
                len = eit - bit;
            next.erase(next.begin()+bit+len, next.begin()+eit+len);

            std::swap(next, seq);
            auto hashv = vec2int();
            auto &mapv = vis[hashv];
            if (!mapv || mapv > d)
            {
                mapv = d;
                if (dfs(d+1, dlim))
                    return true;
            }
            std::swap(next, seq);
        }
    }

    return false;
}

