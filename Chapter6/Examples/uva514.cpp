// Rails, ACM/ICPC CERC 1997, UVa 514

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int N;
    while (cin >> N && N)
    {
        int coach;
        while (cin >> coach && coach)
        {
            vector<int> seq(N-1);
            for (auto &s: seq)
                cin >> s;

            stack<int> st;
            for (auto i = 1; i < coach; ++i)
                st.push(i);

            bool is_out_of_order = false;
            for (auto s: seq)
            {
                if (!st.empty() && s == st.top())
                    st.pop();
                else if (s > coach)
                {
                    for (auto i = coach + 1; i < s; ++i)
                        st.push(i);
                    coach = s;
                }
                else
                {
                    is_out_of_order = true;
                    break;
                }
            }

            cout << (is_out_of_order ? "No\n" : "Yes\n");

            /*if (is_out_of_order)
                cout << "No\n";
            else
                cout << "Yes\n";
                */
        }
        cout << "\n";
    }

    return 0;
}
