#include <stdio.h>

int main()
{
    double sum = 0;
    int i = 0;
    double term = 1;

    do{
        term = 1.0/(2*i+1);
        if (i % 2 == 0)
            sum += term;
        else
            sum -= term;
        ++i;
    }while(!(term < 1e-6));

    printf("%g\n", sum);

    return 0;
}



