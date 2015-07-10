#include <stdio.h>
#include <math.h>

int main()
{
    for(int a = 1; a < 10; ++a)
    {
        for(int b = 0; b < 10; ++b)
        {
            int num = a*1100 + b*11;
            int sqrt_i = floor(sqrt(num)+0.49);
            if (sqrt_i * sqrt_i == num)
                printf("%d\n", num);
        }
    }

    return 0;
}
