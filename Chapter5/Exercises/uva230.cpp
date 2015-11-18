// Borrowers, ACM/ICPC World Finals 1994, UVa 230

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
    using book = pair<string, string>;

    vector<book> shelf;
    map<string, string> t2a; // title to author
    string line;
    while (getline(cin, line) && line != "END")
    {
        auto author_begin = line.find(" by ");
        // {author, title}
        string author = line.substr(author_begin+4);
        string title = get_title(line.substr(0, author_begin));

        shelf.push_back({author, title});
        t2a.insert({std::move(title), std::move(author)});
    }
    sort(shelf.begin(), shelf.end());
    vector<int> onshelf(shelf.size(), 1);

    vector<book> returned;
    while (getline(cin, line) && line != "END")
    {
        string cmd = line.substr(0, 6);
        if (cmd == "BORROW")
        {
            string title = get_title(line.substr(7));
            string author = t2a[title];
            auto it = lower_bound(shelf.begin(), shelf.end(), make_pair(author, title));
            onshelf[distance(shelf.begin(), it)] = 0;
        }
        else if (cmd == "RETURN")
        {
            string title = get_title(line.substr(7));
            string author = t2a[title];
            returned.push_back({author, title});
        }
        else //if (cmd == "SHELVE")
        {
            sort(returned.begin(), returned.end());
            for (const auto &b: returned)
            {
                // cout << b.first << ";" << b.second <<".\n";
                auto it = lower_bound(shelf.begin(), shelf.end(), b);
                auto d = distance(shelf.begin(), it);
                onshelf[d] = 1;
                for (--d; d >= 0 && onshelf[d] == 0; --d);
                if (d >= 0)
                    cout << "Put \"" << b.second << "\" after \"" << shelf[d].second << "\"\n";
                else
                    cout << "Put \"" << b.second << "\" first\n";
            }

            returned.clear();
            cout << "END\n";
        }
    }

    return 0;
}

