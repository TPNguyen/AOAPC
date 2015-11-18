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

        int cur_index = 0;
    public:
        void insert(int digits[], int len, int val)
        {
            int cur_node_index = 0; // at root
            int end = max(0, len-40);
            for (auto i = len-1; i >= end; --i)
            {
                auto d = digits[i];
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

constexpr int max_len = 128;
// apparently 50 is not enough either... amazing ... try 5395363614236562243553349317813301386116
constexpr int precision = 52;
int Fn[2][max_len];

void gen_fibo()
{
    Fn[0][0] = 1;
    Fn[1][0] = 1;

    int can_write = 0, cur = 1;
    int len_write = 1;
    bool len_addand_less = false;
    trie.insert(Fn[0], len_write, 0);
    for (auto id = 2; id < 100000; ++id)
    {
        int carry = 0;
        for (auto i = max(0, len_write-precision); i < len_write -1; ++i)
        {
            Fn[can_write][i] += Fn[cur][i] + carry;
            if (Fn[can_write][i] >= 10)
            {
                Fn[can_write][i] -= 10;
                carry = 1;
            }
            else
                carry = 0;
        }
        Fn[can_write][len_write-1] = (len_addand_less ? 0: Fn[can_write][len_write-1]) + Fn[cur][len_write-1] + carry;
        if (Fn[can_write][len_write-1] >= 10)
        {
            Fn[can_write][len_write-1] -= 10;
            carry = 1;
        }
        else
            carry = 0;
        // /////////////////
        if (carry)
        {
            Fn[can_write][len_write++] = 1;
            len_addand_less = true;
        }
        else
            len_addand_less = false;
        /*for (auto i = len_write-1; i >= max(0, len_write-40); --i)
            cout << Fn[can_write][i];
        cout << '\n';*/

        trie.insert(Fn[can_write], len_write, id);

        if (len_write == max_len)
        {
            copy(std::end(Fn[can_write])-precision, std::end(Fn[can_write]), std::begin(Fn[can_write]));
            copy(std::end(Fn[cur])-precision, std::end(Fn[cur]), std::begin(Fn[cur]));
            /*fill(std::begin(Fn[can_write])+precision, std::end(Fn[can_write]), 0);
            fill(std::begin(Fn[cur])+precision, std::end(Fn[cur]), 0);*/
            len_write = precision;
        }
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

