#include <iostream>

int main()
{
    for (int i = 1; i <= 1<<20; ++i)
        for (int sp = 1; sp <= 1<<10; ++sp)
            for (int sq =1; sq <= 1<<10; ++sq)
                std::cout << i << " " << sp << " " << sq << "\n";

    return 0;
}
