
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
        morse2word.push_back({encoded_morse_code, context_word});
    }
    // print_map(morse2word);

    string morse_word;
    while (cin >> morse_word && morse_word != "*")
    {
        int min_num_dif = MAXL, perf_count = 0;
        string out;
        for(const auto &e: morse2word)
        {
            if (is_prefix(e.first, morse_word))
            {
                auto num_dif = abs(static_cast<int>(e.first.size()) - static_cast<int>(morse_word.size()));
                if (num_dif < min_num_dif)
                {
                    min_num_dif = num_dif;
                    out = e.second;
                }
                if (num_dif == 0)
                    ++perf_count;
            }
        }
        if (min_num_dif == 0)
        {
            cout << out;
            if (perf_count > 1)
                cout << "!";
            cout << "\n";
        }
        else
        {
            cout << out << "?\n";
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

    return iterators.first == a.end() || iterators.second == b.end();
}
