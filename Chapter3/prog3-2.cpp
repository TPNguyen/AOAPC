#include <iostream>
#include <vector>


int main()
{
    using vsize = std::vector<unsigned char>::size_type;
    vsize n, k;
    std::cin >> n >> k;
    std::vector<unsigned char> lit(n+1, 1);

    for (vsize i = 2; i <= k; ++i)
    {
        for (vsize j = i; j <= n; ++j)
        {
            if (j % i == 0)
                lit[j] = !lit[j];
        }
    }

    for (vsize i = 1; i <= n; ++i)
        if (lit[i])
            std::cout << i << " ";

    std::cout << "\n";

    return 0;
}
