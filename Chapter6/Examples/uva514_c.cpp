//#define LOCAL
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

const int maxn = 1000 + 10;
int n, target[maxn];

int main(void)
{
#ifdef LOCAL
    freopen("514in.txt", "r", stdin);
#endif

    while(scanf("%d", &n) == 1 && n)
    {
        while(scanf("%d", &target[1]) == 1 && target[1])
        {
            for(int i = 2; i <= n; ++i)    scanf("%d", &target[i]);
            stack<int> s;
            int A = 1, B = 1;
            int ok = 1;
            while(B <= n)
            {
                if(A == target[B])    { A++; B++; }
                else if(!s.empty() && s.top() == target[B])    { s.pop(); B++; }
                else if(A <= n) s.push(A++);
                else    { ok = 0; break; }
            }
            printf("%s\n", ok ? "Yes" : "No");
        }
        printf("\n");
    }

    return 0;
}
