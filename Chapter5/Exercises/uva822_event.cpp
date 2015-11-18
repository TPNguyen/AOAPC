// Queue and A, ACM/ICPC World Finals 2000, UVa 822

#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Topic {
    int tcost;
} topics[22];

struct Personnel {
    vector<int> plist;
    int pid;
    int tlast;
} staff[5];
auto pesn_cmp = [] (int p1, int p2)
{
    int t1 = staff[p1].tlast, t2 = staff[p2].tlast;
    if (t1 != t2) return t1 < t2;
    return p1 < p2;
};

struct Event {
    int time;
    bool is_new_topic;
    int id;
};
bool operator< (const Event &e1, const Event &e2)
{
    return e1.time < e2.time;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int Kase = 0, num_topics;
    while (cin >> num_topics && num_topics)
    {
        multiset<Event> events;
        unordered_map<int, int> topic2num;
        unordered_map<int, int> topic2index;
        for (auto i = 0; i < num_topics; ++i)
        {
            int tid, num, t0, tcost, dt;
            cin >> tid >> num >> t0 >> tcost >> dt;
            topics[i].tcost = tcost;
            topic2num.insert({tid, 0});
            topic2index.insert({tid, i});
            for (auto j = 0; j < num; ++j)
            {
                events.insert({t0, true, tid});
                t0 += dt;
            }
        }

        int num_pers; cin >> num_pers;
        vector<int> sorted;
        for (int i = 0; i < num_pers; ++i)
        {
            int pid, nlist;
            cin >> pid >> nlist;
            staff[i].pid = i;
            staff[i].tlast = -1; // has to be less than 0, 0 is valid tlast for some case
            staff[i].plist.clear();
            for (auto j = 0; j < nlist; ++j)
            {
                int id; cin >> id;
                staff[i].plist.push_back(id);
            }
            sorted.push_back(i);
        }

        vector<int> freep(num_pers, 1);
        int tot_time;
        for (auto it = events.begin(); it != events.end(); )
        {
            int now = it->time;
            tot_time = now;
            auto pit = events.equal_range(*it);
            for (auto erit = pit.first; erit != pit.second; ++erit)
            {
                if (erit->is_new_topic)
                {
                    topic2num[erit->id]++;
                    //cout << "New topic " << erit->id << " generated at time " << now << '\n';
                }
                else
                {
                    freep[erit->id] = 1;
                    // cout << "Finished: Personnel " << erit->id << " at time " << now << '\n';
                }
            }

            sort(sorted.begin(), sorted.end(), pesn_cmp);

            for (auto p: sorted)
            {
                if (freep[p])
                {
                    for (auto t: staff[p].plist)
                    {
                        if (topic2num[t])
                        {
                            topic2num[t]--;
                            staff[p].tlast = now;
                            events.insert({now+topics[topic2index[t]].tcost, false, p});
                            freep[p] = 0;
                            // cout << "Started: Personnel " << p << " on topic " << t << " at time " << now << "\n";
                            break;
                        }
                    }
                }
            }
            it = events.upper_bound(*it);
        }
        cout << "Scenario " << ++Kase << ": All requests are serviced within " << tot_time << " minutes.\n";
    }

    return 0;
}



