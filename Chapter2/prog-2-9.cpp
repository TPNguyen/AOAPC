#include <iostream>

int main()
{
    int x, n = 0, s = 0;
    int min, max;
    if(std::cin >> x)
    {
        max = min = x;
        n = 1;
        s = x;
    }
    else
    {
        std::cout << "Read number failed.\n";
        return 1;
    }

    while(std::cin >> x)
    {
        s += x;
        if (x < min) min = x;
        if (x > max) max = x;
        ++n;
    }
    std::cout << min << " " << max << " " << (double)s/n << "\n";

    return 0;
}
