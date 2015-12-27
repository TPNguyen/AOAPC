// UVa1451 Average
#include<cstdio>
#include <algorithm>
#include <cassert>
using namespace std;


const int maxn = 100000 + 5;

int n, L;
char s[maxn];
int sum[maxn], p[maxn]; // average of i~j is (sum[j]-sum[i-1])/(j-i+1)

// compare average of x1~x2 and x3~x4
int compare_average(int x1, int x2, int x3, int x4) {
    return (sum[x2]-sum[x1]) * (x4-x3) - (sum[x4]-sum[x3]) * (x2-x1);
}

int main() {
    int T;
    scanf("%d", &T);

    while(T--) {
        scanf("%d%d%s", &n, &L, s+1);

        // std::transform(s+1, s+n+1, sum+1, [](char &c) { return c-'0'; });
        // std::partial_sum(sum, sum+n+1, sum);
        // sum[0] = 0;
        for(int i = 1; i <= n; i++)
        {
            sum[i] = sum[i-1] + s[i] - '0';
        }

        int ansL = 0, ansR = L;

        // p[i..j) is the sequence of candidate start points
        int i = 0, j = 1;
        p[0] = 0;
        for (int t = L+1; t <= n; t++) { // end point
            while (j-i > 1 && compare_average(p[j-2], t-L, p[j-1], t-L) >= 0) j--; // remove concave points
            /*if (j-i > 1 && p[j-1] >= 2)
                assert(s[p[j-1]-1] == '0');*/
            if (s[t-L] == '0')
            p[j++] = t-L; // new candidate

            while (j-i > 1 && compare_average(p[i], t, p[i+1], t) <= 0) i++; // update tangent point

            // compare and update solution
            if (s[t] == '1')
            {
                int c = compare_average(p[i], t, ansL, ansR);
                if (c > 0 || c == 0 && t - p[i] < ansR - ansL) {
                    ansL = p[i]; ansR = t;
                }
            }
        }
        printf("%d %d\n", ansL+1, ansR);
    }
    return 0;
}

