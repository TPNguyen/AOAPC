#include <iostream>
#include <vector>
using namespace std;

int prefix_mask(const vector<unsigned int> &ips);
void print_res(unsigned int na);
int main()
{
    int m;
    while (cin >> m)
    {
        vector<unsigned int> IPs(m);

        for (auto i = 0; i < m; ++i)
        {
            unsigned int ip = 0;
            unsigned int b; char c;

            cin >> b >> c; b &= 0xFF; b <<= 8*3; ip |= b;
            cin >> b >> c; b &= 0xFF; b <<= 8*2; ip |= b;
            cin >> b >> c; b &= 0xFF; b <<= 8*1; ip |= b;
            cin >> b;                            ip |= b;

            IPs[i] = ip;
        }
        int num_leading_1s = prefix_mask(IPs);
        unsigned int mask = (0xFFFFFFFFul) << (32 - num_leading_1s);

        unsigned int network_addr = IPs.front() & mask;

        print_res(network_addr);
        print_res(mask);
    }

    return 0;
}

void print_res(unsigned int na)
{
    int b[4];
    for (auto i = 0; i < 4; ++i)
        b[i] = na>>(8*i) & 0xFF;
    cout << b[3] << "." << b[2] << "." << b[1] << "." << b[0] << "\n";
}

int prefix_mask(const vector<unsigned int> &ips32)
{
    int beg = 1, end = 33;

    int num1s, mask;
    while (beg != end)
    {
        int num1s = beg + (end - beg)/2;
        int mask = ~0 << (32 - num1s);
        int prefix = ips32.front() & mask;
        bool prefix_equal = true;
        for (const auto c: ips32)
            if ((c & mask) != prefix)
            {
                prefix_equal = false;
                break;
            }
        if (prefix_equal)
            beg = num1s + 1;
        else
            end = num1s;
    }

    return beg - 1;
}
