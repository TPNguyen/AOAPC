// Undraw the trees, UVa 10562

#include <cctype>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

void do_undraw(const vector<string> &tr, int level, size_t index);
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
        while (getline(cin, line))
        {
            if (line[0] == '#')
                break;
            if (!line.empty())
                tree.push_back(std::move(line));
        }
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
        auto ind = distance(root.begin(), find_if(root.begin(), root.end(), [](unsigned char const c){return std::isgraph(c);}));
        do_undraw(tr, 0, ind);
    }
    cout << ")\n";
}

void do_undraw(const vector<string> &tr, int level, size_t index)
{
    cout << tr[level][index];
    if (tr.size() > level+1 && tr[level+1][index] == '|')
    {
        cout << "(";
        auto &dash_level = tr[level+2];
        size_t s = index;
        while (s-1 >= 0 && dash_level[s-1] == '-') s--;
        for (; dash_level[s] == '-' && s < tr[level+3].size(); ++s)
            if (isgraph(tr[level+3][s]))    do_undraw(tr, level+3, s);
        cout << ")";
    }
    else 
        cout << "()";
}

