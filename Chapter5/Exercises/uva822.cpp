// Queue and A, ACM/ICPC World Finals 2000, UVa 822

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <unordered_map>
using namespace std;

constexpr int MAXT = 22;
constexpr int MAXP = 6;
struct Topic {
    int tid;
    int num;
    int t0;
    int tcost;
    int tinterv;
} topics[MAXT];

struct Personnel {
    vector<int> list;
    int pid;
    // int num;
    int on_topic;
    int since;
    int last_job_at;
    bool busy;
} persn[MAXP];

auto psn_cmp = [](int p1, int p2)
{
    if (persn[p1].last_job_at != persn[p2].last_job_at)
        return persn[p1].last_job_at < persn[p2].last_job_at;
    else
        return persn[p1].pid < persn[p2].pid;
};

int main()
{
    ios_base::sync_with_stdio(false);
    int Kase = 0, num_topic = 0, num_p;
    while (cin >> num_topic && num_topic)
    {
        int total_request = 0;
        unordered_map<int, int> topic2num;
        unordered_map<int, int> tid2index;
        // fill task info
        for (auto i = 0; i < num_topic; ++i)
        {
            cin >> topics[i].tid >> topics[i].num >> topics[i].t0 >> topics[i].tcost >> topics[i].tinterv;
            total_request += topics[i].num;
            topic2num[topics[i].tid] = 0;
            tid2index[topics[i].tid] = i;
        }

        cin >> num_p;
        for (auto i = 0; i < num_p; ++i)
        {
            int num;
            cin >> persn[i].pid >> num;
            persn[i].pid = i;
            persn[i].last_job_at = -1;
            persn[i].busy = false;
            persn[i].list.resize(num);
            for (auto j = 0; j < num; ++j)
                cin >> persn[i].list[j];
        }

        int total_mins = 0;
        int cur_remaining_task = 0;
        for ( ; total_request; ++total_mins)
        {
// cout << "\nTIME: " << total_mins << "\n";
            // Generate new tasks if there are still
            for (auto i = 0; i < num_topic; ++i)
            {
                int elapsed_time = total_mins - topics[i].t0;
                if (elapsed_time >= 0 && (elapsed_time % topics[i].tinterv == 0) && (elapsed_time / topics[i].tinterv < topics[i].num))
                {
                    ++topic2num[topics[i].tid];
                    ++cur_remaining_task;
                }
            }
/*{
int curnum = 0;
for (auto t: topic2num)
{
    cout << "Topic " << t.first << " Has " << t.second << "\n";
    curnum += t.second;
}
assert(curnum == cur_remaining_task);
}*/
            // Get all free personnel
            vector<int> freep;
            for (auto i = 0; i < num_p; ++i)
            {
                if (!persn[i].busy)
                    freep.push_back(i);
                else if ((total_mins - persn[i].since) % topics[tid2index[persn[i].on_topic]].tcost == 0)
                {
                    freep.push_back(i);
                    persn[i].busy = false;
                    persn[i].last_job_at = persn[i].since;
                    --total_request;
// cout << "Personnel " << persn[i].pid << " finished topic " << topics[tid2index[persn[i].on_topic]].tid << " at " << total_mins << " (started at " << persn[i].since << " min)\n";
                }
            }
            if (cur_remaining_task)
            {
                sort(freep.begin(), freep.end(), psn_cmp);
                for (auto p: freep)
                {
                    for (auto t: persn[p].list)
                        if (topic2num[t])   // have topic to work on
                        {
                            persn[p].busy = true;
                            persn[p].on_topic = t;
                            persn[p].since = total_mins;
                            --topic2num[t];
                            --cur_remaining_task;
// cout << "Personnel " << persn[p].pid << " started topic " << t << " at " << total_mins << "\n";
                            break;
                        }
                    if (!cur_remaining_task)
                        break;
                }
            }
        }

        cout << "Scenario " << ++Kase << ": All requests are serviced within " << --total_mins << " minutes.\n";
    }

    return 0;
}
