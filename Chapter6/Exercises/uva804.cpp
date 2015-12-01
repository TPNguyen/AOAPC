// Petri Net Simulation, ACM/ICPC World Finals 1998, UVa 804

#include <iostream>
#include <vector>
#include <map>
using namespace std;

constexpr int MAXP = 102;
int places[MAXP];
struct Transition
{
    map<int, int> in;
    map<int, int> ot;
    bool can_fire() const
    {
        if (in.empty())
            return false;
        for (auto i: in)
            if (places[i.first] < i.second)
                return false;
        return true;
    }
    void fire() const
    {
        for (auto i: in)
            places[i.first] -= i.second;
        for (auto o: ot)
            places[o.first] += o.second;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    int NP, Kase = 0;
    while (cin >> NP && NP)
    {
        for (auto i = 1; i <= NP; ++i)
            cin >> places[i];

        int NT; cin >> NT;
        vector<Transition> trans(NT+1);
        for (auto i = 1; i <= NT; ++i)
        {
            int inot;
            while (cin >> inot && inot)
            {
                if (inot > 0) // output transitions
                    trans[i].ot[inot]++;
                else
                    trans[i].in[-inot]++;
            }
        }

        int NF; cin >> NF;
        int fire_count = 0;
        bool live = true;
        while (fire_count < NF)
        {
            bool has_can_fire = false;
            for (const auto &t: trans)
                if (t.can_fire())
                {
                    t.fire();
                    has_can_fire = true;
                    fire_count++;
                    break;
                }
            if (!has_can_fire)
            {
                live = false;
                break;
            }
        }

        /*if (fire_count == NF)
        {
            for (const auto &t: trans)
            {
                if (t.can_fire())
                {
                    live = true;
                    break;
                }
            }
        }*/

        cout << "Case " << ++Kase << ":" << (live? " still live " : " dead ") << "after " << fire_count << " transitions\n";
        cout << "Places with tokens:";
        for (auto i = 1; i <= NP; ++i)
            if (places[i])
                cout << " " << i << " (" << places[i] << ")";
        cout << "\n\n";
    }

    return 0;
}
