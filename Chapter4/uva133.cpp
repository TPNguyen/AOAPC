// The Dole Queue

#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>

int pick(int, int, int, int, const std::bitset<32>&);

int main()
{
    int N, k, m;
    std::bitset<32> out;
    while (std::cin >> N >> k >> m && N)
    {
        auto p1 = N-1, p2 = 0;
        auto left = N;
        while (left)
        {
            p1 = pick(p1, 1, k, N, out);
            p2 = pick(p2, -1, m, N, out);
            std::cout << std::setw(3) << p1+1;
            --left;
            if (p2 != p1)
            {
                std::cout << std::setw(3) << p2+1;
                --left;
            }
            out.set(p1); out.set(p2);
            if (left)
                std::cout << ",";
        }

        std::cout << "\n";
        out.reset();
    }

    return 0;
}

// returns in the range 0->N-1
inline int pick(int start, int step, int count, int N, const std::bitset<32> &out)
{
    while (count--)
    {
        do {
            start = (start + step + N) % N;
        } while (out[start]);
    }

    return start;
}

