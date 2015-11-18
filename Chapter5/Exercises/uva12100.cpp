// Printer Queue, ACM/ICPC NWERC 2006, UVa12100
// ref: https://github.com/morris821028/UVa/blob/master/volume121/12100%20-%20Printer%20Queue.cpp

#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int nT; cin >> nT;
    while (nT--)
    {
        int n, m; cin >> n >> m;

        deque<int> pqueue(n);
        for (auto i = 0; i < n; ++i)
            cin >> pqueue[i];
        int my_priority = pqueue[m];
        pqueue[m] = -1;

        int ans = 0;
        while (true)
        {
            auto it2max = max_element(pqueue.begin(), pqueue.end());
            auto max_priority = *it2max;
            if (max_priority == my_priority)
            {
                auto it2myjob = find(pqueue.begin(), pqueue.end(), -1);
                ans += count(pqueue.begin(), it2myjob, my_priority) + 1;
                break;
            }
            else if (max_priority < my_priority)
            {
                ans += 1;
                break;
            }
            else
            {
                while (pqueue.front() != max_priority)
                {
                    pqueue.push_back(pqueue.front());
                    pqueue.pop_front();
                }
                pqueue.pop_front();
                ans += 1;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
