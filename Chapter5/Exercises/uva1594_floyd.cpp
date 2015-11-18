#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int MAXN = 16;
vector<int> Tuple_hare(MAXN);
vector<int> Tuple_tortoise(MAXN);
vector<int> Tuple_zero(MAXN);

inline void move(int n, vector<int> &tuples);
inline bool equal(int n, vector<int> &t1, vector<int> &t2);
int main()
{
    ios_base::sync_with_stdio(false);
    int T;  cin >> T;
    while (T--)
    {
        int n; cin >> n;
        for (auto i = 0; i < n; ++i)
            cin >> Tuple_hare[i];
        Tuple_hare[n] = Tuple_hare[0];
        copy(Tuple_hare.begin(), Tuple_hare.begin()+n, Tuple_tortoise.begin());

        bool found_zero = false;
        for (auto i = 0; i < 1000; ++i)
        {
            move(n, Tuple_hare);
            move(n, Tuple_hare);
            move(n, Tuple_tortoise);
            if (equal(n, Tuple_hare, Tuple_zero) || equal(n, Tuple_tortoise, Tuple_zero))
            {
                found_zero = true;
                break;
            }
            if (equal(n, Tuple_hare, Tuple_tortoise))
            {
                // found_loop = true;
                break;
            }
        }
        if (found_zero)
            cout << "ZERO\n";
        else
            cout << "LOOP\n";
    }

    return 0;
}

void move(int n, vector<int> &tuples)
{
    for (auto i = 0; i < n; ++i)
        tuples[i] = abs(tuples[i] - tuples[i+1]);
    tuples[n] = tuples[0];
}

bool equal(int n, vector<int> &t1, vector<int> &t2)
{
    auto t1_end = t1.begin()+n;
    auto pit = mismatch(t1.begin(), t1_end, t2.begin());

    if (pit.first != t1_end)
        return false;

    return true;
}

