// Unix ls, Uva400

#include <iostream>
#include <array>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

constexpr int MAXN = 110;
int main()
{
    ios_base::sync_with_stdio(false);
    array<string, MAXN> filenames;
    const string hrule(60, '-');
    int N;
    while (cin >> N && N)
    {
        int longest = 0;
        for (auto i = 0; i < N; ++i)
        {
            cin >> filenames[i];
            if (filenames[i].size() > longest)
                longest = filenames[i].size();
        }

        int num_col = (60 - longest)/(longest + 2) + 1;
        int num_row = (N - 1)/num_col + 1;

        sort(filenames.begin(), filenames.begin() + N);

        cout << hrule << "\n";
        for (auto row = 0; row < num_row; ++row)
        {
            for (auto col = 0; col < num_col; ++col)
            {
                auto indx = col * num_row + row;
                if (indx < N)
                    cout << left << setw(col == num_col-1 ? longest : longest + 2) << filenames[indx];
            }
            cout << "\n";
        }

    }

    return 0;
}


