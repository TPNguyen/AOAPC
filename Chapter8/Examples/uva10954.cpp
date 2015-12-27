// Add all, UVa 10954

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int N;
    while (cin >> N && N)
    {
        vector<int> nums(N);
        for (auto i = 0; i < N; ++i)
            cin >> nums[i];

        int ans = 0;
        priority_queue<int, vector<int>, greater<int>> pq(std::greater<int>(), std::move(nums));
        while (pq.size() > 1)
        {
            auto n1 = pq.top(); pq.pop();
            auto n2 = pq.top(); pq.pop();

            ans += n1+n2;
            pq.push(n1+n2);
        }

        cout << ans << "\n";
    }

    return 0;
}
