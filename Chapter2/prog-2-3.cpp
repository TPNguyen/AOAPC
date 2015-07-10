#include <stdio.h>

int main()
{
    for(int root = 1; ; ++root)
    {
        int res = root*root;
        if (res < 1000) continue;
        if (res > 9999) break;
        int first_two_digits = res/100;
        int last_two_digits = res%100;
        if (first_two_digits/10 == first_two_digits%10 && last_two_digits/10 == last_two_digits%10)
            printf("%d\n", res);

    }

    return 0;
}
