#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <utility>
using namespace std;

constexpr int MAXL = 60;
using ms2dict = pair<string, string>;
string Encode(const string &);
bool is_prefix(const string &a, const string &b);
void print_map(const vector<ms2dict> &m)
{
    for (const auto &e: m)
        cout << e.first << " -> " << e.second << "\n";
}

map<char, string> code_mapping;
int main()
{
    char c;
    while (cin >> c && c != '*')
    {
        string morse_code; cin >> morse_code;
        code_mapping[c] = morse_code;
    }

    vector<ms2dict> morse2word;
    string context_word;

    while (cin >> context_word && context_word != "*")
    {
        string encoded_morse_code = Encode(context_word);
        // cout << encoded_morse_code << "\n";
        morse2word.push_back({encoded_morse_code, context_word});
    }

    auto comp = [](const ms2dict p1, const ms2dict p2){ return (p1.first.size() < p2.first.size()) || (p1.first.size() == p2.first.size() && p1.first < p2.first) || (p1.first == p2.first && p1.second.size() < p2.second.size()); };
    // auto comp = [](const ms2dict &p1, const ms2dict &p2){ return (p1.first.size() == p2.first.size())? p1.first < p2.first : p1.first.size() < p2.first.size(); };

    stable_sort(morse2word.begin(), morse2word.end(), comp);

    // print_map(morse2word);

    string morse_word;
    while (cin >> morse_word && morse_word != "*")
    {
        auto its = equal_range(morse2word.begin(), morse2word.end(), make_pair(morse_word, ""), [](const ms2dict &pss, const ms2dict &mw) { return (pss.first.size() < mw.first.size()) || (pss.first.size() == mw.first.size() && pss.first < mw.first); });

        /*if (its.first != morse2word.end())
            cout << its.first->first << " , " << its.first->second << "\n";
        if (its.second != morse2word.end())
            cout << its.second->first << " , " << its.second->second << "\n";
            */
        if (its.first != its.second) // has equal elements, perfect match
        {
            cout << its.first->second;
            if (distance(its.first, its.second) > 1)
            {
                cout << "!";
                // for_each(its.first+1, its.second, [](const ms2dict &pss){cout << pss.second << ",";});
            }
            cout << "\n";
        }
        else // morse word is corrupted, no perfect match
        {
            auto num_truncted = MAXL, num_added = MAXL;
            auto it_long = find_if(its.first, morse2word.end(), [&morse_word](const ms2dict& pss){ return is_prefix(morse_word, pss.first);});
            if (it_long != morse2word.end())
                num_truncted = it_long->first.size() - morse_word.size();

            decltype(morse2word)::reverse_iterator rit_fir{its.first};
            auto it_short = find_if(rit_fir, morse2word.rend(), [&morse_word](const ms2dict& pss){ return is_prefix(pss.first, morse_word);});
            if (it_short != morse2word.rend())
                num_added = morse_word.size() - it_short->first.size();

            if (num_truncted < num_added)
                cout << it_long->second;
            else if (num_added < MAXL)
                cout << it_short->second;
            cout << "?\n";
        }
    }

    return 0;
}

string Encode(const string &cw)
{
    string ret;
    for(const auto &c: cw)
        ret += code_mapping[c];

    return ret;
}

bool is_prefix(const string &a, const string &b)
{
    auto iterators = mismatch(a.begin(), a.end(), b.begin());

    return iterators.first == a.end();
}
