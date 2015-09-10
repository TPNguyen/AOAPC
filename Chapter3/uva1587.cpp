#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

int main()
{
    std::vector<std::pair<int, int>> sides(6);
    int w, h;
    while (std::cin >> w >> h)
    {
        if (w > h) std::swap(w,h);
        sides[0] = {w, h};

        for (auto i = 1; i < 6; ++i)
        {
            std::cin >> w >> h;
            if (w > h) std::swap(w,h);
            sides[i] = {w, h};
        }

        std::sort(std::begin(sides), std::end(sides));

        int x = sides[0].first, y = sides[0].second, z = sides[2].second;
        if (sides[0] == sides[1] && sides[2] == sides[3] && sides[4] == sides[5] &&
                sides[2].first == x && sides[2].second == z &&
                sides[4].first == y && sides[4].second == z)
        {
            std::cout << "POSSIBLE\n";
        }
        else
            std::cout << "IMPOSSIBLE\n";
    }

    return 0;
}

