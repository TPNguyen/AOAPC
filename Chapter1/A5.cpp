#include <stdio.h>

int main()
{
    // compile time error and run time exception (core dump)
    printf("1/0 = %d\n", 1/0);

    return 0;
}
