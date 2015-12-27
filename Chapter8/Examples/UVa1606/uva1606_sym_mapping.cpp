// Amphiphilic Carbon Molecules, ACM?ICPC Shanghai 2004, UVa1606

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

struct P {
    int x, y;
    int t; // 0, 1 == hydrophilic, hydrophobic
} points[1024], wc[1024];

bool colinear(const P &p1, const P &p2)
{
    return p1.y*p2.x == p2.y*p1.x;
}
bool operator<(const P &p1, const P &p2)
{
    /* on x-axis
    if (p1.y == 0)
    {
        if (p2.y == 0) return false;
        return true;
    }

    // on y-axis
    if (p1.x == 0)
    {
        if (p2.x >= 0 && p2.y >= 0) return false;
        return true;
    }

    // in first quardrants
    if (p1.x > 0 && p1.y > 0)
    {
        if (p2.y == 0) return false;
        if (p2.x <= 0) return true;
    }
    else
        if (p2.x >= 0) return false;
        */

    return p1.y*p2.x < p2.y*p1.x;
}

int N;
int main()
{
    ios_base::sync_with_stdio(false);
    while (cin >> N && N)
    {
        for (auto i = 0; i < N; ++i)
            cin >> points[i].x >> points[i].y >> points[i].t;

        int final_max = -1;
        // pick a number as origin
        for (auto i = 0; i < N; ++i)
        {
            P orig = points[i];
            std::transform(points, points+N, wc, [&](const P &op) -> P
                    {
                        P ret{op.x-orig.x, op.y-orig.y, op.t};
                        if (ret.y < 0 || (ret.y == 0 && ret.x < 0))
                        {
                            ret.x = -ret.x; ret.y = -ret.y; ret.t ^= 1;
                        }
                        return ret;
                    });
            std::swap(wc[0], wc[i]);

            sort(wc+1, wc+N);
            int w = std::count_if(wc+1, wc+N, [&](const P &p) { return p.t == 0; });
            int b = N-1-w;
            int cumul_on_line[2] = {0};

            auto itb = 1, ite = itb;
            while (itb < N)
            {
                int on_line[2] = {0};
                for (ite = itb; ite < N; ++ite)
                {
                    if (!colinear(wc[itb], wc[ite])) break;
                    on_line[wc[ite].t]++;
                }
                final_max = max({final_max,
                                 w-on_line[0]+cumul_on_line[1]+ite-itb+1,
                                 b-on_line[1]+cumul_on_line[0]+ite-itb+1});
                // update
                // w -= on_line[0], b -= on_line[1];
                cumul_on_line[0] += on_line[0];
                cumul_on_line[1] += on_line[1];
                w -= on_line[0];
                b -= on_line[1];
                itb = ite;
            }

        }

        cout << final_max << "\n";
    }

    return 0;
}

