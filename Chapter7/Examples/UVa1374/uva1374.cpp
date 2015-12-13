// Power Calculus, ACM/ICPC Yokohama 2006, UVa 1374
//
// Very important lesson: You only need to work on the newly generated number on that depth level.
// No need to generate all possible pairs of numbers with addtion and substraction.
// This is because if there is a need for other combinations (say the first solution need a number
// that is an addition of two numbers which neither is the last generated number), one tree path will
// have created that number at some earlier level while expanding the tree. In other words, since
// the starting point is 1, it can generate all possible numbers and BFS is complete so there is really
// no need to manually generate all pairs. Using only the newly enumerated number with previous numbers
// to generate next numbers is sufficient.
//
// Other points: Only one number greater than the target is needed. This condition can be used for pruning.
// can use vis array to prune out already occurring numbers in the sequence.
// Another very important A* technique is that the newly generated number has to be large enough to satisfy
// num << (depth_limit - cur_depth) > N. Note that num will be the largest value in the sequence most of the
// time. And we don't want in the early tree expansion stage to have many substractions. So this condition
// force the algorithm to get to the 2^d >= N as quickly as possible. As to if this condition still valid
// when num is not the larget number, I guess it doesn't matter. There are just so many ways to additively
// arrive the target. And even if we need to substract to get new numbers, but with such a small number,
// we could easily generated it additively in the early stage of the expansion.
//
// Some observation on IDA*: H() must be admissible. This means that when d==depth_limit, and if last
// number enumerated is not target, we are done on this depth d. Conseqently, there are many ways to
// test if we should return immediately: 1) test H() == 0; 2) test num == target (implying H() == 0 and d==depth_limit)
// 3) if using g()+H() > depth_limit, we don't need to test "if (d == lim)" as the former test
// is stronger.
//
// Ref:
// https://en.wikipedia.org/wiki/Iterative_deepening_A*
// https://github.com/aoapc-book/aoapc-bac2nd/blob/master/ch7/UVa1374.cpp
// http://acm.lilingfei.com/uva-1373-power-calculus-%E4%BE%8B%E9%A2%987-13_50
// https://xuanwo.org/2014/11/02/UVa-1374-Power-Calculus/
// http://blog.csdn.net/L123012013048/article/details/45419745
// http://blog.csdn.net/keshuai19940722/article/details/17638939
// http://bubuko.com/infodetail-908330.html
// http://www.lai18.com/content/1938032.html
// http://www.mamicode.com/info-detail-977045.html
//
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

constexpr int INF = 1025;
int N;
bool found;
int st[16];
int vis[INF];

void dfs_search(int d, int lim);
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
    if (st[d] == N)
    {
        found = true;
        cout << d << "\n";
        return;
    }
    if (d == lim) return;

    if ((st[d] << (lim-d)) < N)
        return;

    for (int i = d; i >= 0; --i)
    {
        st[d+1] = st[d]+st[i];
        if (st[d+1] <= 1024 && !vis[st[d+1]])
        {
            vis[st[d+1]] = 1;
            dfs_search(d+1, lim);
            if (found) return ;
            vis[st[d+1]] = 0;
        }

        st[d+1] = std::abs(st[d]-st[i]);
        if (st[d+1] <= 1024 && !vis[st[d+1]])
        {
            vis[st[d+1]] = 1;
            dfs_search(d+1, lim);
            if (found) return ;
            vis[st[d+1]] = 0;
        }
    }
}
