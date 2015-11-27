// Self-Assembly, ACM/ICPC World Finals 2013, UVa 1572
// http://morris821028.github.io/2014/05/07/oj/uva/uva-1572/
// http://blog.csdn.net/wcr1996/article/details/43637827
// https://github.com/dnr2/maratona/blob/master/UVa/1572%20-%20Self-Assembly.cpp
// http://46aae4d1e2371e4aa769798941cef698.devproxy.yunshipei.com/oilover/article/details/47157061

#include <iostream>
#include <string>
#include <vector>
using namespace std;

constexpr int MAXNODES = 52;
bool has_cycle(const int (&G)[MAXNODES][MAXNODES], int (&has_nodes)[MAXNODES]);
bool topsort(const int ind, const int (&G)[MAXNODES][MAXNODES], int (&has_nodes)[MAXNODES]);

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    while (cin >> n)
    {
        int has_nodes[MAXNODES] {};
        int G[MAXNODES][MAXNODES] {};
        for (auto id = 0; id < n; ++id)
        {
            string label; cin >> label;
            int letters[4] {-1, -1, -1, -1};
            for (auto i = 0; i < label.size(); ++i)
            {
                if (label[i] == '0') continue;
                if (i % 2 == 0)
                    letters[i/2] = label[i]-'A';
                else
                {
                    if (label[i] == '-')
                        letters[i/2] += 26;
                }
            }
            for (auto i = 0; i < 4; ++i)
            {
                if (letters[i] == -1) continue;
                has_nodes[letters[i]] = 1;
                for (auto j = 0; j < 4; ++j)
                {
                    if (j == i) continue;
                    int nexthop = (letters[j]+26)%52;
                    G[letters[i]][nexthop] = 1;
                }
            }
        }

        if (has_cycle(G, has_nodes))
            cout << "unbounded\n";
        else
            cout << "bounded\n";
    }
    return 0;
}

bool has_cycle(const int (&G)[MAXNODES][MAXNODES], int (&has_nodes)[MAXNODES])
{
    for (auto i = 0; i < MAXNODES; ++i)
        if (has_nodes[i] == 1 && !topsort(i, G, has_nodes))
            return true;
    return false;
}

bool topsort(const int ind, const int (&G)[MAXNODES][MAXNODES], int (&has_nodes)[MAXNODES])
{
    // cout << char('A'+ind) << (ind > 25? '-':'+');
    has_nodes[ind] = 2; // visiting
    for (auto i = 0; i < MAXNODES; ++i)
       if (G[ind][i])
       {
           if (has_nodes[i] == 2) // is visiting, has cycle
               return false;
           if (has_nodes[i] == 1) // exist and hasn't been visited yet
               if (topsort(i, G, has_nodes) == false)
                   return false;
       }

    has_nodes[ind] = 3;
    return true;
}
