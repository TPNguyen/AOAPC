// Fabled Rooks, UVa 11134
// Ref:
// http://acm.lilingfei.com/uva-11134-fabled-rooks-%E4%BE%8B%E9%A2%988-4_67
// https://xuanwo.org/2014/11/04/UVa-11134-Fabled-Rooks/
// http://endless.logdown.com/posts/2014/06/15/uva-11134-fabled-rooks-two-dimensional-one-dimensional-greedy
// http://blog.csdn.net/zyq522376829/article/details/46582111
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;

struct interv
{
    int seq;
    int l, r;
};
bool operator<(const interv &lhs, const interv &rhs)
{
    return lhs.r < rhs.r || (lhs.r == rhs.r && lhs.l < rhs.l);
}

array<interv, 5001> Xs, Ys;
array<int, 5001> vis_X, vis_Y;
array<int, 5001> ans_X, ans_Y;

int main()
{
    ios_base::sync_with_stdio(false);
    int N;
    while (cin >> N && N)
    {
        vis_X.fill(-1);
        vis_Y.fill(-1);
        for (auto i = 0; i < N; ++i)
        {
            Xs[i].seq = i; Ys[i].seq = i;
            cin >> Xs[i].l >> Ys[i].l >> Xs[i].r >> Ys[i].r;
        }

        bool impossible = false;
        // X intervals
        std::sort(Xs.begin(), Xs.begin()+N);
        for (auto i = 0; i < N; ++i)
        {
            auto j = Xs[i].l;
            for ( ; j <= Xs[i].r && vis_X[j] != -1; ++j)
            {
            }

            if (j > Xs[i].r)
            {
                impossible = true;
                break;
            }
            else
            {
                vis_X[j] = Xs[i].seq;
                ans_X[Xs[i].seq] = j;
            }
        }

        // Y intervals
        if (!impossible)
        {
            std::sort(Ys.begin(), Ys.begin()+N);
            for (auto i = 0; i < N; ++i)
            {
                auto j = Ys[i].l;
                for ( ; j <= Ys[i].r && vis_Y[j] != -1; ++j)
                {
                }

                if (j > Ys[i].r)
                {
                    impossible = true;
                    break;
                }
                else
                {
                    vis_Y[j] = Ys[i].seq;
                    ans_Y[Ys[i].seq] = j;
                }
            }
        }

        if (impossible)
            cout << "IMPOSSIBLE\n";
        else
        {
            for (auto i = 0; i < N; ++i)
            {
                cout << ans_X[i] << " " << ans_Y[i] << "\n";
            }
        }
    }

    return 0;
}

