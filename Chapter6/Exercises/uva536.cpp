// Tree Recovery, UVa 536

#include <iostream>
#include <string>
using namespace std;

string get_post(const string &pre, const string &in);
int main()
{
    string pre, in;
    while (cin >> pre >> in)
        cout << get_post(pre, in) << "\n";

    return 0;
}

string get_post(const string &pre, const string &in)
{
    if (pre.empty() || in.empty())
        return string();

    auto root_index = in.find_first_of(pre[0]);
    if (root_index != string::npos)
        return get_post(pre.substr(1, root_index), in.substr(0, root_index))
             + get_post(pre.substr(1+root_index), in.substr(root_index+1))
             + pre[0];
}
