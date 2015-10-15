// Cube painting

#include <string>
#include <iostream>
#include <functional>
using namespace std;

bool is_rotational_equivalent(const string &a, const string &b);
string rotate_x_axis(const string &in)
{
    // rotate ccw: int seq[] = {5, 1, 3, 4, 6, 2};
    return string({in[5-1], in[1-1], in[3-1], in[4-1], in[6-1], in[2-1]});
}

string rotate_y_axis(const string &in)
{
    // rotate ccw: int seq[] = {1, 3, 5, 2, 4, 6};
    string ret(in);
    int j = 0;
    for (auto i:  {1, 3, 5, 2, 4, 6})
        ret[j++] = in[i-1];

    return ret;
}
string rotate_z_axis(const string &in)
{
    // rotate ccw: int seq[] = {4, 2, 1, 6, 5, 3};
    string ret(in);
    int j = 0;
    for (auto i:  {4, 2, 1, 6, 5, 3})
        ret[j++] = in[i-1];

    return ret;
}

template <typename func>
string rotate_n_times(int n, const string &s, func f)
{
    string ret{s};
    for(auto i = 0; i < n; ++i)
        ret = f(ret);

    return ret;
}

int main()
{
    string line;
    while (cin >> line)
    {
        string first = line.substr(0, 6);
        string second = line.substr(6, 6);

        if (is_rotational_equivalent(first, second))
            cout << "TRUE\n";
        else
            cout << "FALSE\n";
    }

    return 0;
}

bool is_rotational_equivalent(const string &a, const string &b)
{
    function<string (const string&)> fps[] = {rotate_x_axis, rotate_y_axis, rotate_z_axis};
    int rot_seq[6][3] = { {0, 0, 0}, {3, 0, 0}, {0, 0, 3}, {0, 0, 1}, {1, 0, 0}, {0, 0, 2}};
    for (const auto &arr: rot_seq)
    {
        string temp{a};
        for (auto i = 0; i < 3; ++i)
            temp = rotate_n_times(arr[i], temp, fps[i]);

        for (auto i = 0; i < 4; ++i)
        {
            temp = rotate_n_times(i, temp, fps[1]);
            if (temp == b)
                return true;
        }
    }

    return false;
}

/*string rotate_x_n_times(int n, const string &s)
{
    string ret{s};
    for(auto i = 0; i < n; ++i)
        ret = rotate_x_axis(ret);

    return ret;
}
string rotate_y_n_times(int n, const string &s)
{
    string ret{s};
    for(auto i = 0; i < n; ++i)
        ret = rotate_y_axis(ret);

    return ret;
}*/



    

