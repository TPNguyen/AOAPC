// uva815 - Flooded!
#include <array>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

int main()
{
    array<int, 1000> squares;
    int m, n;
    int kase = 0;
    double eps = 1e-4;
    while (cin >> m >> n && m && n)
    {
        ++kase;
        int totalnum = m*n;
        for (auto i = 0; i < totalnum; ++i)
            cin >> squares[i];

        int total_water; cin >> total_water;

        sort(squares.begin(), squares.begin() + totalnum);
        int accumulated = 0;

        auto i = 0;
        for ( ; i < totalnum-1 && accumulated < total_water; ++i)
        {
            auto height_diff = squares[i+1] - squares[i];
            auto cubic_water = height_diff * 100 * (i+1);
            accumulated += cubic_water;
        }

        double final_height = squares[i];
        if (accumulated < total_water)
        {
            final_height = static_cast<double>((total_water-accumulated))/(100*totalnum) + squares[totalnum-1];
            ++i;
        }
        else if (total_water < accumulated)
            final_height = squares[i] - static_cast<double>((accumulated-total_water))/(100*i);

        cout << fixed << setprecision(2);
        cout << "Region " << kase << "\n";
        cout << "Water level is " << final_height + eps << " meters.\n";
        cout << static_cast<double>(i*100)/totalnum << " percent of the region is under water.\n\n";
    }

    return 0;
}
