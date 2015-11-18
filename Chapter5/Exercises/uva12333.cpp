// Revenge of Fibonacci, ACM/ICPC Shanghai 2011, UVa12333

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

class Trie {
    private:
        struct trieNd {
            int nexts[10];
            int val;
        } Nds[4000000];

        int cur_index;
    public:
        void insert(const vector<int> &num, int val)
        {
            int cur_node_index = 0; // at root
            for (const auto d: num)
            {
                if (Nds[cur_node_index].nexts[d] == 0)
                {
                    Nds[cur_node_index].nexts[d] = ++cur_index;
                    Nds[cur_index].val = val;
                }
                cur_node_index = Nds[cur_node_index].nexts[d];
            }
        }
        int query(const string &num)
        {
            int cur_node_index = 0; // at root
            for (const auto c: num)
            {
                cur_node_index = Nds[cur_node_index].nexts[c-'0'];
                if (cur_node_index == 0)
                    return -1;
            }
            return Nds[cur_node_index].val;
        }
} trie;

constexpr int base = 1E9;
// the 100000'th fibonacci number has about 20900 digits and since base is 9 digits, we need about 20900/9+1 places to hold the largest fibonacci number.
int Fn[2][2400];

vector<int> get_digits(int arr[], int len)
{
    vector<int> ret;
    int n = arr[len-1];
    int div = 1E8;
    bool is_leading_zero = true;
    for (int rounds = 0; rounds < 9; ++rounds, div/= 10)
    {
        int digit = n/div%10;
        if (is_leading_zero)
        {
            if(!digit)
                continue;
            else
                is_leading_zero = false;
        }
        ret.push_back(digit);
    }
    for (auto i = len-2; i >= max(0, len-6); --i)
    {
        n = arr[i];
        div = 1E8;
        for (int rounds = 0; rounds < 9; ++rounds, div/= 10)
        {
            int digit = n/div%10;
            ret.push_back(digit);
        }
    }

    if (ret.size() > 40)
        ret.resize(40);

    /*for (const auto i: ret)
        cout << i;
    cout << "\n";*/

    return ret;
}

void gen_fibo()
{
    Fn[0][0] = 1;
    Fn[1][0] = 1;

    int can_write = 0, cur = 1;
    int len = 1;
    trie.insert(get_digits(Fn[0], len), 0);
    for (auto i = 2; i < 100000; ++i)
    {
        // should be len - 7 since we need at least 52 most significant digits
        for (auto i = max(0, len-7); i < len; ++i)
        {
            Fn[can_write][i] += Fn[cur][i];
            if (Fn[can_write][i] >= base)
            {
                ++Fn[can_write][i+1];
                Fn[can_write][i] %= base;
            }
        }
        if (Fn[can_write][len])
            ++len;
        trie.insert(get_digits(Fn[can_write], len), i);
        std::swap(can_write, cur);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    gen_fibo();
    int T;
    cin >> T;
    for (auto i = 1; i <= T; ++i)
    {
        string digits;
        cin >> digits;
        cout << "Case #" << i << ": " << trie.query(digits) << "\n";

    }

    return 0;
}
