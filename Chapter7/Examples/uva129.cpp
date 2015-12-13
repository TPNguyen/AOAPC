// Krypton Factor, UVa 129

#include <iostream>
#include <string>
using namespace std;

int nth, L;
bool dfs(int &cur, string res);

int main()
{
    ios_base::sync_with_stdio(false);
    while (cin >> nth >> L && nth)
    {
        string res;
        int cnt = 0;
        dfs(cnt, res);
    }

    return 0;
}

bool no_repeat(const string &s)
{
    auto totlen = s.size();
    for (auto len = 1; len <= totlen/2; ++len)
    {
        if (s.substr(totlen-len, len) == s.substr(totlen-2*len, len))
            return false;
    }

    return true;
}

bool dfs(int &cur, string res)
{
    if (cur == nth)
    {
        auto totlen = res.size();
        for (auto i = 0; i < totlen; ++i)
        {
            if (i % 64 == 0 && i)
                cout << "\n";
            else if (i % 4 == 0 && i)
                cout << " ";
            cout << res[i];
        }
        cout << "\n";
        cout << totlen << "\n";
        return true;
    }
    for (auto i = 0; i < L; ++i)
    {
        if (no_repeat(res + char('A'+i)))
            if (dfs(++cur, res+char('A'+i)))
                return true;
    }
    return false;
}
