// Updating a Dictionary, UVa 12504

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <algorithm>
using namespace std;

vector<string> mapped_v;
vector<string> key_v;
auto cmp_key = [](const int &m1, const int &m2) { return key_v[m1] < key_v[m2];};
map<int, int, decltype(cmp_key)> dict1(cmp_key), dict2(cmp_key);
using mapping = map<int, int, decltype(cmp_key)>::value_type;

auto cmp = [](const mapping &m1, const mapping &m2) { return key_v[m1.first] < key_v[m2.first];};

void populate(decltype(dict1) &dict, vector<string> &kval, vector<string> &mval)
{
    string line;
    getline(cin, line);
    auto keyb = find_if(line.begin(), line.end(), [](const char c) { return islower(c); });
    while (keyb != line.end())
    {
        auto keye = find_if(keyb, line.end(), [](const char c) { return c==':';});
        auto valb = keye + 1;
        auto vale = find_if(valb, line.end(), [](const char c) { return c==',' || c=='}';});
        kval.emplace_back(keyb, keye);
        mval.emplace_back(valb, vale);
        dict.insert({kval.size()-1, mval.size()-1});
        // update keyb iterator
        keyb = ++vale;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    string line;
    getline(cin, line); int T = stoi(line);
    while (T--)
    {
        populate(dict1, key_v, mapped_v);
        populate(dict2, key_v, mapped_v);
        // sort(dict[0].begin(), dict[0].end(), cmp);
        // sort(dict[1].begin(), dict[1].end(), cmp);

        vector<mapping> insection;
        set_intersection(dict1.begin(), dict1.end(), dict2.begin(), dict2.end(), back_inserter(insection), cmp);

        using iter_T = map<int, int, decltype(cmp_key)>::iterator;
        // check if added new keys
        vector<mapping> added;
        if (insection.size() != dict2.size())
            set_difference(make_move_iterator(dict2.begin()), make_move_iterator(dict2.end()), insection.begin(), insection.end(), back_inserter(added), cmp);
        // check if removed keys
        vector<mapping> removed;
        if (insection.size() != dict1.size())
            set_difference(make_move_iterator(dict1.begin()), make_move_iterator(dict1.end()), insection.begin(), insection.end(), back_inserter(removed), cmp);
        // check if changed
        vector<mapping> changed;
        copy_if(make_move_iterator(insection.begin()), make_move_iterator(insection.end()), back_inserter(changed), [](const mapping &m){ return mapped_v[m.second] != mapped_v[dict2[m.first]];});

        bool first_add = true, first_rem = true, first_change = true;
        if (added.size())
        {
            cout << "+";
            for (const auto &k: added)
            {
                if (first_add) first_add = false;
                else cout << ",";
                cout << key_v[k.first];
            }
            cout << "\n";
        }

        if (removed.size())
        {
            cout << "-";
            for (const auto &k: removed)
            {
                if (first_rem) first_rem = false;
                else cout << ",";
                cout << key_v[k.first];
            }
            cout << "\n";
        }

        if (changed.size())
        {
            cout << "*";
            for (const auto &k: changed)
            {
                if (first_change) first_change = false;
                else cout << ",";
                cout << key_v[k.first];
            }
            cout << "\n";
        }

        if (first_add && first_rem && first_change)
            cout << "No changes\n";

        cout << "\n";
        mapped_v.clear();
        key_v.clear();
        dict1.clear();
        dict2.clear();
    }

    return 0;
}




