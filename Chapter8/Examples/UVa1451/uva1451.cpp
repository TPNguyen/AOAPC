// Average, Seoul 2009, UVa 1451

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
using namespace std;

inline int compare_slope(int s1, int t1, int s2, int t2, const vector<int> &psum);
int main()
{
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    while (T--)
    {
        int n, L;
        string dna;
        cin >> n >> L >> dna;

        // partial sum doesnt' work here b/c the range of value is only the range of characters
        std::for_each(dna.begin(), dna.end(), [](char &c) { c -= '0';});
        vector<int> psum(n+1); psum[0] = 0;
        std::partial_sum(dna.begin(), dna.end(), psum.begin()+1);

        int ansL = 0, ansR = L;
        deque<int> convex_pts{0};
        for (auto t = L+1; t <= n; ++t)
        {
            // if (dna[t-L-1] == 0)
            //     convex_pts.push_back(t-L); // psum index starts with 1 since 0 means partial sum of nothing
            while (convex_pts.size() > 1 &&
                    compare_slope(convex_pts[convex_pts.size()-2], t-L, convex_pts[convex_pts.size()-1], t-L, psum) >= 0)
                convex_pts.pop_back(); // remove concave points

            convex_pts.push_back(t-L);

            while (convex_pts.size() > 1 && compare_slope(convex_pts[0], t, convex_pts[1], t, psum) <= 0)
            {
                convex_pts.pop_front();
            }

            int c = compare_slope(convex_pts[0], t, ansL, ansR, psum);
            if (c > 0 || c == 0 && t - convex_pts[0] < ansR - ansL)
                ansL = convex_pts[0], ansR = t;
        }

        cout << ansL+1 << " " << ansR << "\n";
    }

    return 0;
}

int compare_slope(int s1, int t1, int s2, int t2, const vector<int> &psum)
{
    return (psum[t1]-psum[s1])*(t2-s2) - (psum[t2]-psum[s2])*(t1-s1);
}
