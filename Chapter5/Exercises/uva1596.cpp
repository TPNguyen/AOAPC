// Bug Hunt, ACM/ICPC Tokyo 2007, UVa1596

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cctype>
using namespace std;

// data
map<char, pair<int, map<int, int>>> arr2contents;
using map_it = map<char, pair<int,map<int, int>>>::iterator;
// functions
bool create_arr(const string &line);
inline map_it check_arr_exist(const string &line);
int get_index(const string &line);
int check(const string &line);

int main()
{
    ios_base::sync_with_stdio(false);
    string line;
    while (getline(cin, line) && line != ".")
    {
        int first_bugline = 0,  linenum = 0;
        bool invalid = false;
        do {
            if (!invalid)
            {
                ++linenum;
                auto iequl = line.find_first_of('=');
                if (iequl == string::npos)
                {
                    if(!create_arr(line))
                        invalid = true;
                }
                else
                {
                    string lhs = line.substr(0, iequl);
                    string rhs = line.substr(iequl+1);
                    auto arr_it = check_arr_exist(line);
                    if (arr_it != arr2contents.end())
                    {
                        auto eval_arg = get_index(lhs.substr(2, lhs.size()-3));
                        if (eval_arg >= 0 && eval_arg < arr_it->second.first)
                        {
                            // get right hand value
                            int rhv = -1;
                            if (isdigit(rhs[0]))
                                rhv = stoi(rhs);
                            else
                                rhv = get_index(rhs);

                            if (rhv == -1)
                                invalid = true;
                            else
                                arr_it->second.second[eval_arg] = rhv;
                        }
                        else
                            invalid = true;
                    }
                    else
                        invalid = true;
                }

                if (invalid)
                    first_bugline = linenum;
            }
        } while(getline(cin, line) && line != ".");

        if (!invalid)
            cout << "0\n";
        else
            cout << first_bugline << "\n";

        arr2contents.clear();
    }

    return 0;
}

bool create_arr(const string &line)
{
    char arr_name = line[0];
    int bound = get_index(line.substr(2, line.size()-3));
    if (bound < 0)
        return false;
    return arr2contents.insert({arr_name, {bound, map<int,int>()}}).second;
}

inline map_it check_arr_exist(const string &line)
{
    char arr_name = line[0];
    auto it = arr2contents.find(arr_name);
    // if (it == arr2contents.end())
    return it;
}

int get_index(const string &line)
{
    int ans;
    if (isdigit(line[0]))
        ans = stoi(line);
    else
    {
        auto it = check_arr_exist(line);
        if (it == arr2contents.end())
            return -1;

        ans = -1;
        string argument = line.substr(2, line.size()-3);
        int index = get_index(argument);

        if (index >= 0 && index < it->second.first)
        {
            auto ins_r = it->second.second.find(index);
            if (ins_r != it->second.second.end())
                ans = ins_r->second;
        }
    }

    return ans;
}

/*int check(const string &line)
{
    int *v = nullptr;
    auto r = check_bound(line, &v);
    if (r && v != nullptr)
        return *v;
    else
        return -1;
}*/




