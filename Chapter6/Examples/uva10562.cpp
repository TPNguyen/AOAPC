// Undraw the trees, UVa 10562

#include <cctype>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

void do_undraw(const vector<string> &tr, int level, size_t start, size_t end);
void undraw_tree(const vector<string> &tr);

int main()
{
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    string line;
    getline(cin, line); // remove the newline after T
    while (T--)
    {
        vector<string> tree;
        /*while (getline(cin, line) && line.empty());
        tree.push_back(std::move(line));*/
        while (getline(cin, line) && line[0] != '#')
            tree.push_back(std::move(line));
        undraw_tree(tree);
    }

    return 0;
}

void undraw_tree(const vector<string> &tr)
{
    cout << "(";
    if (!tr.empty())
    {
        auto &root = tr[0];
        do_undraw(tr, 0, 0, root.size());
    }
    cout << ")\n";
}

void do_undraw(const vector<string> &tr, int level, size_t start, size_t end)
{
    auto &root_line = tr[level];
    while (true)
    {
        auto ind = distance(root_line.begin(), find_if(root_line.begin()+start, root_line.begin()+end, [](unsigned char const c){return std::isgraph(c);}));
        if (ind == end) break;
        cout << root_line[ind];
        if (tr.size() > level+1 && tr[level+1][ind] == '|')
        {
            cout << "(";
            auto &dash_level = tr[level+2];
            size_t s = 0, e = 0;
            do {
                s = dash_level.find_first_of('-', e);
                e = dash_level.find_first_not_of('-', s);
            } while (s != string::npos && e != string::npos && !(s <= ind && e > ind));
            if (e == string::npos || e >= tr[level+3].size())
                e = tr[level+3].size();
            do_undraw(tr, level+3, s, e);
            cout << ")";
        }
        else
            cout << "()";
        start = ind+1;
    }
}
