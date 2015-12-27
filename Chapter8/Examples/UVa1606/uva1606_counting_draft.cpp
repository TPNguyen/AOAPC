// Amphiphilic Carbon Molecules, ACM?ICPC Shanghai 2004, UVa1606
// Ref:
// http://www.xlgps.com/article/168377.html
// https://xuanwo.org/2014/11/04/UVa-1606-Amphiphilic-Carbon-Molecules/

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

struct P {
    int x, y;
    int t; // 0, 1 == hydrophilic, hydrophobic
    int seq;
} points[1024], wc[1024];

bool colinear(const P &p1, const P &p2)
{
    return p1.y*p2.x == p2.y*p1.x;
}
bool operator<(const P &p1, const P &p2)
{
    return p1.y*p2.x < p2.y*p1.x;
}

int N;
int main()
{
    ios_base::sync_with_stdio(false);
    while (cin >> N && N)
    {
        for (auto i = 0; i < N; ++i)
        {
            cin >> points[i].x >> points[i].y >> points[i].t;
            points[i].seq = i;
        }

        int final_max = -1;
        // pick a number as origin
        for (auto i = 0; i < N; ++i)
        {
            P orig = points[i];
            std::transform(points, points+N, wc, [&](const P &op) -> P
                    {
                        P ret{op.x-orig.x, op.y-orig.y, op.t, op.seq};
                        if (ret.y < 0 || (ret.y == 0 && ret.x < 0))
                        {
                            ret.x = -ret.x; ret.y = -ret.y; ret.t ^= 1;
                        }
                        return ret;
                    });
            std::swap(wc[0], wc[i]);

            sort(wc+1, wc+N);
            int w = std::count_if(wc+1, wc+N, [&](const P &p) { return p.t == 0; });
            int b = 0;

            auto itb = 1, ite = itb;
            while (itb < N)
            {
                int lw = 0;
                bool has_new_elements = false;
                for (ite = itb; ite < N; ++ite)
                {
                    if (wc[ite].seq > i) has_new_elements = true;
                    if (!colinear(wc[itb], wc[ite])) break;
                    if (wc[ite].t) b++;
                    else lw ++;
                }
                // w contains white dots on the line; b is all the cumulative blacks so far (including on the line).
                // N-1 - b is all the blacks (excluding dots on the line) on that side and all whites.
                // N-1 - b - w is all the blacks as above plus whites on the other side.
                // Hard to wrap your head around the summation. Look alternatives in sym_mapping version.
                if (has_new_elements)
                    final_max = max({final_max, w+b+1, N-w-b+ite-itb});
                // update
                w -= lw;
                itb = ite;
            }

        }

        cout << final_max << "\n";
    }

    return 0;
}


