#include <cmath>
#include <cstring>
#include <cstdio>

using namespace std;
const double eps = 1e-6;
const double LOG2_10 = log2(10.0);

char s[100];

int main()
{
    unsigned long long M, E, b;
    double a, A, tmp;
    while (scanf("%s", s), strcmp(s, "0e0"))
    {
        *strchr(s, 'e') = 32;
        sscanf(s, "%lf%llu", &a, &b);
        A = log2(a) + b * LOG2_10;
        for(M = 0; M < 10; ++M)
        {
            tmp = log2(1 - 1.0 / (1 << (M + 1)));
            E = (unsigned long long)round(log2(A - tmp + 1));
            if (fabs(A - ((1 << E) - 1) - tmp) < eps) break;
        }
        printf("%llu %llu\n", M, E);
    }
    return 0;
}
