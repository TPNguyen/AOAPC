// Boxes i a line, UVa 12657

#include <list>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int n, m, kase = 0;
    while (cin >> n >> m)
    {
        list<int> boxes;
        vector<list<int>::iterator> viters;
        for (auto i = 0; i <= n; ++i)
        {
            boxes.push_back(i);
            viters.push_back(--boxes.end());
        }

        int op, X, Y;
        bool reversed = false;
        while (m--)
        {
            cin >> op;
            if (op == 4) reversed = !reversed;
            else {
                cin >> X >> Y;
                if (op != 3 && reversed) op = 3-op;
                if (op == 1)
                {
                    auto it = viters[X];
                    if (*++it == Y)
                        continue;
                }
                if (op == 2)
                {
                    auto it = viters[X];
                    if (*--it == Y)
                        continue;
                }
            }

            if (op == 1)
            {
                auto it = boxes.insert(viters[Y], X);
                boxes.erase(viters[X]);
                viters[X] = it;
            }

            if (op == 2)
            {
                auto ity = viters[Y];
                auto it = boxes.insert(++ity, X);
                boxes.erase(viters[X]);
                viters[X] = it;
            }

            if (op == 3)
            {
                std::swap(viters[X], viters[Y]);
                std::swap(*viters[X], *viters[Y]);
            }
        }

        // auto i = reversed? (n%2 ? 1 : 2) : 1;
        auto it = ++boxes.begin();
        auto it_end = boxes.end();
        if (reversed && n%2 == 0)
            ++it;
        long long ans = 0;
        while (it != it_end)
        {
            ans += *it;
            ++it;
            if (it != it_end)
               ++it;
        }

        cout << "Case " << ++kase << ": " << ans << "\n";
    }

    return 0;
}
