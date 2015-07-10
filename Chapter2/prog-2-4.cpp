#include <stdio.h>

int main()
{
    long long n = 1;
    int  count = 0;
    scanf("%lld", &n);

    while(n != 1)
    {
        if (n % 2) // n is odd
            n = 3*n+1;
        else
            n /= 2;
        ++count;
    }

    printf("%d\n", count);

    return 0;
}
