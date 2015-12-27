// Amphiphilic Carbon Molecules, ACM?ICPC Shanghai 2004, UVa1606
// Another method based on atan2 + crossproduct testing colinearity
// https://github.com/morris821028/UVa/blob/master/temp/1606%20-%20Amphiphilic%20Carbon%20Molecules.cpp
// http://www.cnblogs.com/AOQNRMGYXLMV/p/4277934.html
// http://www.cnblogs.com/LLGemini/p/4309425.html
// http://blog.csdn.net/weizhuwyzc000/article/details/46763451
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

struct P {
    int x, y;
    int t; // 0, 1 == hydrophilic, hydrophobic
} points[1024];

bool operator<(const P &p1, const P &p2)
{
    // on x-axis
    if (p1.y == 0)
    {
        if (p2.y == 0) return false;
        return true;
    }

    // on y-axis
    if (p1.x == 0)
    {
        if (p2.x >= 0 && p2.y >= 0 || p2.x <= 0 && p2.y <= 0) return false;
        return true;
    }

    // in first/third quardrants
    if (p1.x > 0 && p1.y > 0 || p1.x < 0 && p1.y < 0)
    {
        if (p2.y == 0) return false;
        if (p2.x * p2.y <= 0) return true;
    }
    else
        if (p2.x * p2.y >= 0) return false;
    if (p2.x * p1.x > 0) // same quadrant
        return p1.y*p2.x < p2.y*p1.x;
    else
        return p1.y*p2.x > p2.y*p1.x;
}

int N;
int main()
{
    ios_base::sync_with_stdio(false);
    while (cin >> N && N)
    {
        for (auto i = 0; i < N; ++i)
            cin >> points[i].x >> points[i].y >> points[i].t;

        int t_tot[2] = {0};
        for_each(points, points+N, [&](const P &p) { t_tot[p.t]++; });

        int final_max = 0;
        // pick a number as origin
        for (auto i = 0; i < N; ++i)
        {
            P orig = points[i];
            vector<P> wc{points, points+N}; std::swap(wc[0], wc[i]);
            int t[2] = {0}, cur_max = 0, num_orig = 0;
            int t_tot_except_orig[2] = {t_tot[0], t_tot[1]};
            for_each(wc.begin(), wc.end(), [&](P &ap) {
                    ap.x -= orig.x; ap.y -= orig.y;
                    if (ap.y > 0 || ap.y == 0 && ap.x > 0)
                        t[ap.t]++;
                    else if (ap.x == 0 && ap.y == 0)
                    {
                        num_orig++;
                        t_tot_except_orig[ap.t]--;
                    }
                });

            sort(wc.begin()+1, wc.end());
            int diff_t[2] = {0};
            auto itb = wc.begin(), ite = wc.end();
            while (itb != wc.end())
            {
                t[0] += diff_t[0], t[1] += diff_t[1];

                std::tie(itb, ite) = equal_range(itb, wc.end(), *itb);
                diff_t[0] = diff_t[1] = 0;
                int t_on_line[2] = {0};
                // points from quadrants 1, 2 are excluded; 3, 4 included. on positive axies excluded.
                // since points on the line can be counted as on either side, they all should be excluded.
                for_each(itb, ite, [&](const P &ap) {
                        if (ap.y > 0 || ap.y == 0 && ap.x > 0)
                        {
                            t[ap.t]--;
                            t_on_line[ap.t]++;
                        }
                        else if (!(ap.x == 0 && ap.y == 0))
                        {
                            diff_t[ap.t]++;
                            t_on_line[ap.t]++;
                        }
                    });
                int sumt0 = t[0]+t_on_line[0], sumt1 = t[1]+t_on_line[1];
                cur_max = max(cur_max, num_orig+t_on_line[0]+t_on_line[1]+max(t[0]+t_tot_except_orig[1]-sumt1, t[1]+t_tot_except_orig[0]-sumt0));

                // update
                itb = ite;
            }

            final_max = max(final_max, cur_max);
        }

        cout << final_max << "\n";
    }

    return 0;
}
