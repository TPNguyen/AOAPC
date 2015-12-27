// Fabled Rooks, UVa 11134

#include <iostream>
#include <vector>
#include <algorithm>
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

int main()
{
    ios_base::sync_with_stdio(false);
    int N;
    while (cin >> N && N)
    {
        vector<interv> Xs(N), Ys(N);
        for (auto i = 0; i < N; ++i)
        {
            Xs[i].seq = i; Ys[i].seq = i;
            cin >> Xs[i].l >> Ys[i].l >> Xs[i].r >> Ys[i].r;
        }

        bool impossible = false;
        vector<int> ans_X(N), ans_Y(N);
        // X intervals
        std::sort(Xs.begin(), Xs.end());
        for (auto i = 1; i <= N; ++i)
        {
            auto j = 0;
            for ( ; j < N; ++j)
            {
                if (Xs[j].l <= i && Xs[j].r >= i)
                {
                    ans_X[Xs[j].seq] = i;
                    Xs[j].r = Xs[j].l;
                    break;
                }
            }
            if (j == N)
            {
                impossible = true;
                break;
            }
        }

        // Y intervals
        if (!impossible)
        {
            std::sort(Ys.begin(), Ys.end());
            for (auto i = 1; i <= N; ++i)
            {
                auto j = 0;
                for ( ; j < N; ++j)
                {
                    if (Ys[j].l <= i && Ys[j].r >= i)
                    {
                        ans_Y[Ys[j].seq] = i;
                        Ys[j].r = Ys[j].l;
                        break;
                    }
                }
                if (j == N)
                {
                    impossible = true;
                    break;
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
