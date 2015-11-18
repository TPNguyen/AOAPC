// Borrowers, ACM/ICPC World Finals 1994, UVa 230
// Ref: https://github.com/ksaveljev/UVa-online-judge/blob/master/230.cpp
// http://www.hardbird.net/uva-230-borrowers/
// http://blog.csdn.net/wcr1996/article/details/40898767

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

inline string get_title(const string &quoted)
{
    auto i = quoted.find_first_of('"');
    auto j = quoted.find_first_of('"', i+1);
    return quoted.substr(i+1, j-i-1);
}
int main()
{
    ios_base::sync_with_stdio(false);
    using book = pair<string, string>;

    vector<book> shelf;
    map<string, int> t2i; // title to index
    string line;
    while (getline(cin, line) && line != "END")
    {
        auto author_begin = line.find(" by ");
        // {author, title}
        string author = line.substr(author_begin+4);
        string title = get_title(line.substr(0, author_begin));

        shelf.push_back({std::move(author), std::move(title)});
    }
    sort(shelf.begin(), shelf.end());
    for (auto i = 0; i < shelf.size(); ++i)
        t2i[shelf[i].second] = i;
    vector<int> onshelf(shelf.size(), 1);

    vector<int> returned;
    while (getline(cin, line) && line != "END")
    {
        string cmd = line.substr(0, 6);
        if (cmd == "BORROW")
        {
            string title = get_title(line.substr(7));
            onshelf[t2i[title]] = 0;
        }
        else if (cmd == "RETURN")
        {
            string title = get_title(line.substr(7));
            returned.push_back(t2i[title]);
        }
        else //if (cmd == "SHELVE")
        {
            sort(returned.begin(), returned.end());
            for (const auto &b: returned)
            {
                auto d = b;
                onshelf[d] = 1;
                for (--d; d >= 0 && onshelf[d] == 0; --d);
                if (d >= 0)
                    cout << "Put \"" << shelf[b].second << "\" after \"" << shelf[d].second << "\"\n";
                else
                    cout << "Put \"" << shelf[b].second << "\" first\n";
            }

            returned.clear();
            cout << "END\n";
        }
    }

    return 0;
}

