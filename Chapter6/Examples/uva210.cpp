// Concurrencey Simulator, ACM/ICPC World Finals 1991, UVa210

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int Kase = 0; cin >> Kase;
    while (Kase--)
    {
        int np, tassign, tprint, tlock, tunlock, tend, tquantum;
        cin >> np >> tassign >> tprint >> tlock >> tunlock >> tend >> tquantum;
        vector<vector<string>> programs(np);
        string line; getline(cin, line); // get rid of the newline in current line
        for (auto iprog = 0; iprog < np && getline(cin, line) && line != ""; )
        {
            bool is_end = line == "end";
            programs[iprog].push_back(std::move(line));
            if (is_end)
                iprog++;
        }

        deque<int> readyq;
        for (auto i = 0; i < np; ++i)
            readyq.push_back(i);
        queue<int> blockedq;
        vector<int> prog_counter(np);
        vector<int> var(26);
        bool is_locked = false;

        while (!readyq.empty())
        {
            int cur_prog = readyq.front();
            readyq.pop_front();

            int time_elapsed = 0;
            bool is_out = false;
            /*bool is_blocked = false;
            bool is_ended = false;*/
            while (time_elapsed < tquantum)
            {
                string cur_statement = programs[cur_prog][prog_counter[cur_prog]];
                if (cur_statement.find("lock") == 0)
                {
                    if (is_locked)
                    {
                        is_out = true;
                        blockedq.push(cur_prog);
                        break;
                    }
                    else
                    {
                        time_elapsed += tlock;
                        is_locked = true;
                    }
                }
                else if (cur_statement.find("unlock") == 0)
                {
                    time_elapsed += tunlock;
                    is_locked = false;
                    if (!blockedq.empty())
                    {
                        int next_ready = blockedq.front();
                        blockedq.pop();
                        readyq.push_front(next_ready);
                    }
                }
                else if (cur_statement.find("end") == 0)
                {
                    is_out = true;
                    break;
                }
                else if (cur_statement.find("print") == 0)
                {
                    time_elapsed += tprint;
                    int index_space = cur_statement.find_first_of(' ');
                    int index_var = cur_statement.find_first_not_of(' ', index_space+1);
                    cout << cur_prog+1 << ": " << var[cur_statement[index_var]-'a'] << "\n";
                }
                else // setting variable values
                {
                    time_elapsed += tassign;
                    int equal_sign_index = cur_statement.find_first_of('=');
                    int val = stoi(cur_statement.substr(equal_sign_index+1));
                    var[cur_statement[0]-'a'] = val;
                }
                prog_counter[cur_prog]++;
            }
            if (!is_out)
                readyq.push_back(cur_prog);
        }

        if (Kase)
            cout << "\n";
    }

    return 0;
}


// Other Sources:
// http://blog.csdn.net/wcr1996/article/details/43637795
// http://blog.csdn.net/acvay/article/details/43054111
