#include <vector>
#include <iostream>
using namespace std;

int prefix_mask(const vector<int> &bytes);
int main()
{
    int m;
    while (cin >> m)
    {
        vector<int> bytes[4];
        for (auto i = 0; i < m; ++i)
        {
            int b; char c;
            for (auto j = 0; j < 3; ++j)
            {
                cin >> b >> c;
                bytes[j].push_back(b);
            }
            cin >> b;
            bytes[3].push_back(b);
        }

        /*for (auto i = 0; i < 4; ++i)
        {
            for (auto cont: bytes[i])
                cout << cont << " ";
            cout << "\n";
        }*/

        int equal_to = 0;
        vector<int> network_addr(4), network_mask(4);
        for (; equal_to < 4; ++equal_to)
        {
            int cur_byte = bytes[equal_to].front();
            bool all_equal = true;
            for (const auto c: bytes[equal_to])
            {
                if (c != cur_byte)
                {
                    all_equal = false;
                    break;
                }
            }
            if (!all_equal)
                break;
            else
            {
                network_addr[equal_to] = cur_byte;
                network_mask[equal_to] = (1 << 8) - 1;
            }
        }

        if (equal_to < 4)
        {
            int mask = prefix_mask(bytes[equal_to]);
            mask = ((1 << mask) - 1) << (8 - mask);
            // cout << mask << "\n";
            network_addr[equal_to] = bytes[equal_to].front() & mask;
            network_mask[equal_to] = mask;
        }

        for (auto i = 0; i < 3; ++i)
            cout << network_addr[i] << ".";
        cout << network_addr[3] << "\n";

        for (auto i = 0; i < 3; ++i)
            cout << network_mask[i] << ".";
        cout << network_mask[3] << "\n";
    }

    return 0;
}

int prefix_mask(const vector<int> &bytes)
{
    int beg = 1, end = 9;

    int num1s, mask;
    while (beg != end)
    {
        // cout << beg << ", " << end << "; ";
        int num1s = beg + (end - beg)/2;
        // cout << num1s << " ";
        int mask = ~0 << (8 - num1s);
        // cout << mask << " ";
        int prefix = bytes.front() & mask;
        // cout << prefix << "\n";
        bool prefix_equal = true;
        for (const auto c: bytes)
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





