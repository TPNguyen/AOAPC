// Non-boring sequences, CERC 2012, UVa 1608

#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
using namespace std;

constexpr int INF = 1<<30;
struct LFRT
{
    int left = -1;
    int right = INF;
};

bool has_unique(const vector<int> &seq, unordered_map<int, LFRT> &leftright, int s, int t);

int main()
{
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    while (T--)
    {
        int n; cin >> n;

        vector<int> seq(n);
        for (auto i = 0; i < n; ++i)
            cin >> seq[i];
        bool not_boring = false;
        bool is_boring = false;
        for (auto i = 0; i < n-1; ++i)
        {
            if (seq[i] == seq[i+1])
            {
                is_boring = true;
                break;
            }
        }

        unordered_map<int, int> num2loc;
        unordered_map<int, LFRT> leftright;
        if (!is_boring)
        {
            for (auto i = 0; i < n; ++i)
            {
                leftright.insert({i, LFRT()});
                if (num2loc.count(seq[i]))
                {
                    auto pre_loc = num2loc[seq[i]];
                    leftright[pre_loc].right = i;
                    leftright[i].left = pre_loc;
                }
                num2loc[seq[i]] = i;
            }

            if (num2loc.size() == n)
                not_boring = true;
        }
        // try to see if it is a boring seq
        if (is_boring)
            cout << "boring\n";
        else if (not_boring)
            cout << "non-boring\n";
        else
        {
            not_boring = has_unique(seq, leftright, 0, seq.size()-1);

            if (not_boring)
                cout << "non-boring\n";
            else
                cout << "boring\n";
        }
    }

    return 0;
}

bool has_unique(const vector<int> &seq, unordered_map<int, LFRT> &leftright, int s, int t)
{
    if (t <= s) return true;
    bool found = false;
    int loc;
    for (auto front = s, back = t; front <= back; ++front, --back)
    {
        if (leftright[front].left < s && leftright[front].right > t)
        {
            // found a unique element between s and t;
            loc = front;
            found = true;
            break;
        }
        else if (back > front && leftright[back].left < s && leftright[back].right > t)
        {
            loc = back;
            found = true;
            break;
        }
    }
    if (!found)
        return false;

    if (has_unique(seq, leftright, s, loc-1) && has_unique(seq, leftright, loc+1, t))
        return true;

    return false;
}

/*bool has_unique(unordered_map<int, vector<int>> &num2loc, map<int, list<int>> &len2num, int s, int t)
{
    if (t <= s) return true;
    bool found = false;
    int loc;
    for (auto &m: len2num)
    {
        for (auto it = m.second.begin(); it != m.second.end(); ++it)
        {
            auto hi_it = std::upper_bound(num2loc[*it].begin(), num2loc[*it].end(), t);
            auto lo_it = std::lower_bound(num2loc[*it].begin(), num2loc[*it].end(), s);
            if (hi_it-lo_it == 1)
            {
                // found a unique element between s and t;
                loc = *lo_it;
                // num2loc[*it].erase(lo_it);
                if (m.first > 1)
                    len2num[m.first-1].push_back(*it);
                // else
                    // num2loc.erase(*it);
                m.second.erase(it);
                found = true;
                break;
            }
        }

        if (found)
            break;
    }

    if (!found)
        return false;

    if (has_unique(num2loc, len2num, s, loc-1) && has_unique(num2loc, len2num, loc+1, t))
        return true;

    return false;
}*/
/*
        for (auto i = 0; i < n-1; ++i)
        {
            if (seq[i] == seq[i+1])
            {
                is_boring = true;
                break;
            }
        }
        for (auto &n: num2loc)
        {
            leftright[n.second.front()] = {-1, n.second[1]};
            for (auto i = 1; i < n.second.size()-1; ++i)
                leftright[n.second[i]] = {n.second[i-1], n.second[i+1]};
            leftright[n.second.back()] = {n.second[n.second.size()-2], INF};
        }
        map<int, list<int>> len2num;
        for (const auto &m: num2loc)
            len2num[m.second.size()].push_back(m.first);

        if (len2num[1].size() == n) // all unique
            is_boring = false;
        else if (len2num[1].empty()) // no unique
            is_boring = true;
        if (!is_boring) 
            auto mid = num2loc[len2num[1].back()].back();
            len2num[1].pop_back();
        */
