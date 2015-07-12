#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

int main()
{
    int count = 0;
    std::string s;
    std::cin >> s;
    for(int abc = 100; abc < 1000; ++abc)
        for(int de = 10; de < 100; ++de)
        {
            int x = abc*(de%10), y = abc*(de/10), z = abc*de;
            std::ostringstream buf;
            buf << abc << de << x << y << z;
            int ok = 1;
            for(const auto &c : buf.str())
            {
                if(s.find(c) == std::string::npos)
                    ok = 0;
            }
            if(ok)
            {
                printf("<%d>\n", ++count);
                printf("%5d\nX%4d\n-----\n%5d\n%4d\n-----\n%5d\n\n", abc, de, x, y, z);
            }
        }

    printf("The number of solutions = %d\n", count);
    // Undefined behavior. Sequence point violation.
    printf("%d %d %d\n", count++, count++, count++);
    char b = 'c', c = 'd';
    char const * const a = &b;
    a = &c; // should fail
    *a = 'e'; // should fail


    return 0;
}


