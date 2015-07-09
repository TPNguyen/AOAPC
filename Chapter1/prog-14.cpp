#include <stdio.h>
#include <utility>

// print out 3 numbers in ascending order
int main()
{
    int a, b, c, t;
    scanf("%d%d%d", &a, &b, &c);
    if (a > b)
    {
        std::swap(a, b);
    }
    if (a > c)
    {
        std::swap(a, c);
    }
    if (b > c)
    {
        std::swap(b, c);
    }

    printf("%d %d %d\n", a, b, c);

    return 0;
}
