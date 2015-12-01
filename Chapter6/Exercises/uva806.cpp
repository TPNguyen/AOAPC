// Spatial Structures, ACM/ICPC World Finals 1998, UVa 806
// http://www.cnblogs.com/137033036-wjl/p/4890068.html
// https://github.com/morris821028/UVa/blob/master/volume008/806%20-%20Spatial%20Structures.cpp
// http://blog.csdn.net/crazysillynerd/article/details/43882593

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

constexpr int MAXN = 64;
char Graph[MAXN][MAXN];
struct quad_tree_node
{
    int color;
    quad_tree_node *children[4];
};

void clear_black_block(const int i, const int j, const int len);
void print_num(int N);
bool is_all_black(const int i, const int j, const int len);
int get_encoding(int i, int j, int len, int tot_len);
void print_grid(vector<int> &codes, int N);
void set_black(int i , int j, int len);
vector<int> base5(int c);

int main()
{
    ios_base::sync_with_stdio(false);
    int N, Kase = 0;
    while (cin >> N && N)
    {
        vector<int> blacks;
        auto len = abs(N);
        if (Kase)
            cout << "\n";
        cout << "Image " << ++Kase << "\n";
        if (N > 0) // 0/1 representation
        {
            cin.ignore(100, '\n');
            char c;
            for (auto i = 0; i < len; ++i)
            {
                for (auto j = 0; j < len; ++j)
                {
                    cin.get(c); Graph[i][j] = c-'0';
                }
                cin.ignore(100, '\n');
            }

            print_num(len);
        }
        else
        {
            memset(Graph, 0, sizeof(Graph));
            int encode;
            while (cin >> encode && encode != -1)
                blacks.push_back(encode);

            print_grid(blacks, len);
        }
    }

    return 0;
}

void print_grid(vector<int> &codes, int N)
{
    for (auto c: codes)
    {
        vector<int> encodes = base5(c);
        auto i = 0, j = 0, len = N;
        for (auto d: encodes)
        {
            len /= 2;
            i += d > 2? len : 0;
            j += d % 2? 0 : len;
        }

        set_black(i, j, len);
    }

    for (auto i = 0; i < N; ++i)
    {
        for (auto j = 0; j < N; ++j)
        {
            if (Graph[i][j])
                cout << "*";
            else
                cout << ".";
        }
        cout << "\n";
    }
}

void set_black(int i , int j, int len)
{
    for (int I = i; I < i+len; ++I)
        for (int J = j; J < j+len; ++J)
            Graph[I][J] = 1;
}

vector<int> base5(int c)
{
    constexpr int base = 5;
    vector<int> ret;
    while (c)
    {
        ret.push_back(c%base);
        c /= base;
    }
    return ret;
}

bool is_all_black(const int i, const int j, const int len)
{
    for (auto I = i; I < i + len; ++I)
        for (auto J = j; J < j + len; ++J)
            if (!Graph[I][J])
                return false;
    return true;
}

void clear_black_block(const int i, const int j, const int len)
{
    for (auto I = i; I < i + len; ++I)
        for (auto J = j; J < j + len; ++J)
            Graph[I][J] = 0;
}

int get_encoding(int i, int j, int len, int tot_len)
{
    int ret = 0;
    int base = 1;
    while (tot_len > len)
    {
        tot_len >>= 1;
        int bit1 = (tot_len & i)? 1 : 0;
        int bit0 = (tot_len & j)? 1 : 0;
        int digit = (bit1<<1) + bit0 + 1;
        ret += digit * base;
        base *= 5;
    }
    return ret;
}

void print_num(int N)
{
    vector<int> ans;
    for (auto i = 0; i < N; ++i)
    {
        for (auto j = 0; j < N; ++j)
        {
            if (Graph[i][j])    // this is black
            {
                int bits = 1;
                int max_len = 1;
                while (bits <= N && (bits & i) == 0 && (bits & j) == 0)
                {
                    if (is_all_black(i, j, bits<<1))
                    {
                        max_len = bits << 1;
                        bits <<= 1;
                    }
                    else break;
                }

                ans.push_back(get_encoding(i, j, max_len, N));
                clear_black_block(i, j, max_len);
            }
        }
    }

    sort(ans.begin(), ans.end());
    int count = 0;
    for (const auto e: ans)
    {
        if (count % 12 == 0)
            cout << e;
        else
            cout << " " << e;
        if (++count % 12 == 0)
            cout << "\n";
    }
    if (count % 12 != 0) cout << "\n";

    cout << "Total number of black nodes = " << ans.size() << "\n";
}



