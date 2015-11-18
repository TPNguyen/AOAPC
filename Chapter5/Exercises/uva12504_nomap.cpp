// Updating a Dictionary, UVa 12504

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

vector<string> mapped_v;
vector<string> key_v;
using mapping = pair<int, int>;
vector<mapping> dict1, dict2;

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
        dict.push_back({kval.size(), mval.size()});
        kval.emplace_back(keyb, keye);
        mval.emplace_back(valb, vale);
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
        sort(dict1.begin(), dict1.end(), cmp);
        sort(dict2.begin(), dict2.end(), cmp);

        auto dict1_b = dict1.begin();
        auto dict1_e = dict1.end();
        auto dict1_size = dict1.size();
        vector<int> dict1_not_removed(dict1_size);
        vector<int> added, changed;
        for (const auto &kv: dict2)
        {
            auto pit = equal_range(dict1_b, dict1_e, kv, cmp);
            if (pit.first != pit.second)
            {
                if (mapped_v[pit.first->second] != mapped_v[kv.second])
                    changed.push_back(kv.first);
                dict1_not_removed[distance(dict1_b, pit.first)] = 1;
            }
            else
                added.push_back(kv.first);
        }

        size_t has_add = 0, has_rem = 0, has_change = 0;
        if (has_add = added.size())
        {
            cout << "+";
            cout << key_v[added[0]];
            for (auto i = 1; i < has_add; ++i)
                cout << "," << key_v[added[i]];
            cout << "\n";
        }

        auto iremove = 0;
        for (; iremove < dict1_size; ++iremove)
        {
            if (!dict1_not_removed[iremove])
            {
                cout << "-" << key_v[dict1[iremove].first];
                has_rem++;
                break;
            }
        }
        for (++iremove; iremove < dict1_size; ++iremove)
        {
            if (!dict1_not_removed[iremove])
                cout << "," << key_v[dict1[iremove].first];
        }
        if (has_rem)
            cout << "\n";

        if (has_change = changed.size())
        {
            cout << "*";
            cout << key_v[changed[0]];
            for (auto i = 1; i < has_change; ++i)
                cout << "," << key_v[changed[i]];
            cout << "\n";
        }

        if (!has_add && !has_rem && !has_change)
            cout << "No changes\n";

        cout << "\n";
        mapped_v.clear();
        key_v.clear();
        dict1.clear();
        dict2.clear();
    }

    return 0;
}





