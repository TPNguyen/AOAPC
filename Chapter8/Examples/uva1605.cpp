// Building for UN, ACM/ICPC NEERC 2007, UVa 1605

#include <iostream>
using namespace std;

int main()
{
    int N;
    while (cin >> N)
    {
        cout << '2' << " " << N << " " << N << "\n";
        for (auto i = 0; i < N; ++i)
        {
            for (auto j = 0; j < N; ++j)
            {
                if (i < 26)
                    cout << static_cast<char>('A'+i);
                else
                    cout << static_cast<char>('a'+i-26);
            }
            cout << "\n";
        }
        cout << "\n";
        for (auto i = 0; i < N; ++i)
        {
            for (auto j = 0; j < N; ++j)
            {
                if (j < 26)
                    cout << static_cast<char>('A'+j);
                else
                    cout << static_cast<char>('a'+j-26);
            }
            cout << "\n";
        }
    }

    return 0;
}


