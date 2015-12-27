// Stacks of Flapjacks, UVa120

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int sizes[36], scount;

void flip();
void substack_flip(int bottom);
int main()
{
    ios_base::sync_with_stdio(false);
    char line[256] = {'\0'};
    while (cin.getline(line, 255))
    {
        line[cin.gcount()-1] = '\n';
        line[cin.gcount()] = '\0';
        char *nc = nullptr, *lp = line;
        scount = 0;
        do {
            int s = strtol(lp, &nc, 10);
            if (s)
                sizes[scount++] = s;
            lp = nc;
        } while (*nc != '\n');

        cout << line;
        flip();
    }

    return 0;
}

void flip()
{
    vector<int> sorted_sizes(sizes, sizes+scount);
    std::sort(sorted_sizes.begin(), sorted_sizes.end(), greater<int>());
    while (1)
    {
        if (is_sorted(sizes, sizes+scount))
        {
            cout << "0\n";
            return;
        }

        for (auto i = 0; i < scount; ++i)
        {
            int cur_size = sorted_sizes[i];
            auto cur_sizep = std::find(sizes, sizes+scount, cur_size);
            // in position already
            if ((cur_sizep - sizes) == (scount-i-1))
                continue;
            // flip twice
            {
                substack_flip(cur_sizep - sizes);
                substack_flip(scount-i-1);
            }
        }
    }
}

void substack_flip(int bottom)
{
    if (bottom > 0)
        cout << scount - bottom << " ";
    int top = 0;
    while (top < bottom)
    {
        std::swap(sizes[top], sizes[bottom]);
        top++;
        bottom--;
    }

    /*cout << ":";
    for (auto i = 0; i < scount; ++i)
        cout << sizes[i] << " ";
    cout << "\n";*/
}




