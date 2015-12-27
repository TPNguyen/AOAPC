// Foul Play, ACM/ICPC NWERC 2012, UVa 1609

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

constexpr int MAXN = 1026;
char beat[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    int NT;
    while (cin >> NT)
    {
        for (auto i = 0; i < NT; ++i)
            cin >> beat[i];

        unordered_set<int> strong, A_can_beat;
        for (auto i = 1; i < NT; ++i)
        {
            if (beat[0][i] == '0')
                strong.insert(i);
            else
                A_can_beat.insert(i);
        }

        unordered_map<int, vector<int>> useful;
        for (auto it = A_can_beat.begin(); it != A_can_beat.end(); )
        {
            auto b = *it;
            bool is_useful = false;
            for (const auto &s: strong)
                if (beat[b][s] == '1')
                {
                    useful[b].push_back(s);
                    is_useful = true;
                }
            if (is_useful)
                it = A_can_beat.erase(it);
            else
                ++it;
        }

        vector<int> defeated(NT);
        for (; NT > 1; NT >>= 1)
        {
            // stage 1
            for (auto it = useful.begin(); it != useful.end(); )
            {
                auto g = *it;
                while (!g.second.empty() && defeated[g.second.back()])
                    g.second.pop_back();
                if (!g.second.empty())
                {
                    cout << g.first+1 << " " << g.second.back()+1 << "\n";
                    defeated[g.second.back()] = 1;
                    strong.erase(g.second.back());
                    g.second.pop_back();
                    ++it;
                }
                else
                {
                    A_can_beat.insert(g.first);
                    it = useful.erase(it);
                }
            }
            // stage 2
            cout << "1 " << *A_can_beat.begin()+1 << "\n";
            A_can_beat.erase(A_can_beat.begin());
            // stage 3
            auto ita = strong.begin(), itb = ita;
            if (itb != strong.end())
                ++itb;
            while (ita != strong.end() && itb != strong.end())
            {
                decltype(ita) erasing;
                if (beat[*ita][*itb] == '1')
                {
                    cout << *ita+1 << " " << *itb+1 << "\n";
                    defeated[*itb] = 1;
                    erasing = itb;
                }
                else
                {
                    cout << *itb+1 << " " << *ita+1 << "\n";
                    defeated[*ita] = 1;
                    erasing = ita;
                }

                ++ita; ++ita;
                if (ita != strong.end())
                {
                    ++itb;
                    if (itb != strong.end())
                        ++itb;
                }
                strong.erase(erasing);
            }
            // stage 4
            if (ita != strong.end()) // has remaining strong
            {
                cout << *ita+1 << " " << *A_can_beat.begin()+1 << "\n";
                A_can_beat.erase(A_can_beat.begin());
            }
            auto it_beat1 = A_can_beat.begin(), it_beat2 = it_beat1;
            if (it_beat2 != A_can_beat.end())
                ++it_beat2;
            while (it_beat1 != A_can_beat.end() && it_beat2 != A_can_beat.end())
            {
                decltype(it_beat1) erasing;
                if (beat[*it_beat1][*it_beat2] == '1')
                {
                    cout << *it_beat1+1 << " " << *it_beat2+1 << "\n";
                    erasing = it_beat2;
                }
                else
                {
                    cout << *it_beat2+1 << " " << *it_beat1+1 << "\n";
                    erasing = it_beat1;
                }
                ++it_beat1; ++it_beat1;
                if (it_beat1 != A_can_beat.end())
                {
                    ++it_beat2; ++it_beat2;
                }
                A_can_beat.erase(erasing);
            }
        }
    }

    return 0;
}


