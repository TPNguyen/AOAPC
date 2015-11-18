// Compound Words, UVa10391

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    vector<string> words;
    set<int> wordlens;

    string w;
    while (cin >> w)
    {
        words.push_back(w);
        wordlens.insert(w.size());
    }

    for (const auto &w: words)
    {
        for (const auto &l: wordlens)
        {
            if (l >= w.size())
                break;
            if (binary_search(words.begin(), words.end(), w.substr(0,l)) &&
                    binary_search(words.begin(), words.end(), w.substr(l)))
            {
                cout << w << "\n";
                break;
            }
        }
    }

    return 0;
}

