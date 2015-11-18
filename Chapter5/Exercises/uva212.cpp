// Use of Hospital Facilities, ACM/ICPC World Finals 1991, UVa212
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
using namespace std;

constexpr int INF = 1<<11;
// Operating room
struct OR {
    static int min_prep;
    int patient;
    int total_mins = 0;
    int next_avai_time = 0;
    int end_time = 0;
};
int OR::min_prep;

// Recovery Bed
struct RB {
    static int min_prep;
    int patient;
    int total_mins = 0;
    int next_avai_time = 0;
    int end_time = 0;
};
int RB::min_prep;

// Patient
struct Pat {
    static int min_transport;
    string lname;
    int min_surgery;
    int min_recovery;
    int OR_i = -1;
    int OR_start = -1; //  OR_end;
    int RB_i = -1;
    int RB_start = -1; //  RB_end;
    Pat(string &&s, int min_s, int min_r): lname(std::move(s)), min_surgery(min_s), min_recovery(min_r)
    {}
};
int Pat::min_transport;
int st_hour, num_or, num_rb, mins_transport, num_pat;
vector<OR> orooms;
vector<RB> rbeds;
vector<Pat> patients;

// Lambdas
auto wait_or_cmp = [](int a, int b) -> bool
{
    if (orooms[a].next_avai_time != orooms[b].next_avai_time)
        return orooms[a].next_avai_time < orooms[b].next_avai_time;
    return a < b;
};
auto busy_or_cmp = [](int a, int b) -> bool
{
    if (orooms[a].end_time != orooms[b].end_time)
        return orooms[a].end_time < orooms[b].end_time;
    // return orooms[a].patient < orooms[b].patient;
    return a < b;
};
auto wait_bed_cmp = [](int a, int b) -> bool
{
    if (rbeds[a].next_avai_time != rbeds[b].next_avai_time)
        return rbeds[a].next_avai_time < rbeds[b].next_avai_time;
    return a < b;
};
auto busy_bed_cmp = [](int a, int b) -> bool
{
    if (rbeds[a].end_time != rbeds[b].end_time)
        return rbeds[a].end_time < rbeds[b].end_time;
    return a < b;
};
// free ORs
set<int, decltype(wait_or_cmp)> or_free_list(wait_or_cmp);
// waiting ORs
// set<int, decltype(wait_or_cmp)> or_wait_list(wait_or_cmp);
// busy ORs
set<int, decltype(busy_or_cmp)> or_busy_list(busy_or_cmp);

// available RBs
set<int> rb_free_list;
// busy RBs
set<int, decltype(busy_bed_cmp)> rb_busy_list(busy_bed_cmp);
// wait RBs
set<int, decltype(wait_bed_cmp)> rb_wait_list(wait_bed_cmp);

void print_res(int lastt);
void assign_pat_or(int t, queue<int> &pq)
{
    while (!pq.empty() && !or_free_list.empty() && orooms[*or_free_list.begin()].next_avai_time == t)
    {
        int or_num = *or_free_list.begin();
        OR &oroom = orooms[or_num];
        Pat &pat = patients[pq.front()];
        oroom.patient = pq.front();
        oroom.end_time = t + pat.min_surgery;
        oroom.next_avai_time = oroom.end_time + OR::min_prep;
        oroom.total_mins += pat.min_surgery;

        pat.OR_i = or_num;
        pat.OR_start = t;
        // pat.OR_end = oroom.end_time;

        or_busy_list.insert(or_num);
        or_free_list.erase(or_free_list.begin());

        pq.pop();
        // cout << "Patient " << oroom.patient+1 << ": " << pat.lname << " enters OR " << pat.OR_i << " at " << pat.OR_start << "\n";
    }
}

void assign_pat_rb(queue<int> &pqrb)
{
    while (!pqrb.empty() && !rb_free_list.empty())
    {
        int p_num = pqrb.front();
        Pat &p = patients[p_num];
        // if (p.RB_start != t) return;
        int rb_num = *rb_free_list.begin();
        p.RB_i = rb_num;

        RB &rbed = rbeds[rb_num];
        rbed.patient = p_num;
        rbed.end_time = p.RB_start + p.min_recovery;
        rbed.next_avai_time = rbed.end_time + RB::min_prep;
        rbed.total_mins += p.min_recovery;

        rb_busy_list.insert(rb_num);
        rb_free_list.erase(rb_free_list.begin());
        pqrb.pop();
        // cout << "Patient " << p_num+1 << ": " << p.lname << " enters RB " << p.RB_i << " at " << p.RB_start << "\n";
    }
}

void release_pat_or(int t, queue<int> &rb_wait_q)
{
    while (!or_busy_list.empty() && orooms[*or_busy_list.begin()].end_time == t)
    {
        int or_num = *or_busy_list.begin();
        OR &oroom = orooms[or_num];
        Pat &pat = patients[oroom.patient];

        rb_wait_q.push(oroom.patient);
        pat.RB_start = t + Pat::min_transport;
        // pat.RB_end = rbed.end_time;

        or_free_list.insert(or_free_list.end(), or_num);
        or_busy_list.erase(or_busy_list.begin());
        // cout << "Patient " << oroom.patient+1 << ": " << pat.lname << " leaves OR " << or_num << " at " << t << "\n";
    }
    assign_pat_rb(rb_wait_q);
}

void release_pat_rb(int t, queue<int> &h_q)
{
    while (!rb_busy_list.empty() && rbeds[*rb_busy_list.begin()].end_time == t)
    {
        int rb_num = *rb_busy_list.begin();
        RB &rbed = rbeds[rb_num];

        h_q.push(rbed.patient);

        rb_wait_list.insert(rb_wait_list.end(), rb_num);
        rb_busy_list.erase(rb_busy_list.begin());

        // cout << "Patient " << rbed.patient+1 << ": " << patients[rbed.patient].lname << " leaves RB " << rb_num << " at " << t << "\n";
    }
}

void release_waiting_rb(int t)
{
    while (!rb_wait_list.empty() && rbeds[*rb_wait_list.begin()].next_avai_time == t)
    {
        rb_free_list.insert(*rb_wait_list.begin());
        rb_wait_list.erase(rb_wait_list.begin());
    }
}



int main()
{
    ios_base::sync_with_stdio(false);
    while (cin >> num_or >> num_rb >> st_hour >> Pat::min_transport >> OR::min_prep >> RB::min_prep >> num_pat) {
        orooms = vector<OR>(num_or);
        rbeds = vector<RB>(num_rb);
        patients.clear();

        or_free_list.clear();
        or_busy_list.clear();
        rb_free_list.clear();
        rb_wait_list.clear();
        rb_busy_list.clear();

    for (auto i = 0; i < num_pat; ++i)
    {
        string lname; int min_s, min_r;
        cin >> lname >> min_s >> min_r;
        patients.emplace_back(std::move(lname), min_s, min_r);
    }

    // create lists of available ORs, busy ORs, available RBs, busy RBs.
    for (auto i = 0; i < num_or; ++i)
        or_free_list.insert(i);

    for (auto i = 0; i < num_rb; ++i)
        rb_free_list.insert(i);


    // Start Simulation
    queue<int> pat_q;
    queue<int> healed_q;
    for (auto i = 0; i < num_pat; ++i)
        pat_q.push(i);
    assign_pat_or(0, pat_q);

    queue<int> waiting_rb;
    while (healed_q.size() != num_pat)
    {
        int time_free_or = (pat_q.empty() || or_free_list.empty()) ? INF : orooms[*or_free_list.begin()].next_avai_time;
        int time_busy_or = or_busy_list.empty() ? INF : orooms[*or_busy_list.begin()].end_time;

        int time_wait_rb = rb_wait_list.empty() ? INF : rbeds[*rb_wait_list.begin()].next_avai_time;
        int time_busy_rb = rb_busy_list.empty() ? INF : rbeds[*rb_busy_list.begin()].end_time;

        // int time_patient_waiting_rb = waiting_rb.empty() ? INF : patients[waiting_rb.front()].RB_start - Pat::min_transport;
        int cur_time = min({time_wait_rb, time_free_or, time_busy_or, time_busy_rb});

        if (cur_time == time_busy_rb)
        {
            release_pat_rb(cur_time, healed_q);
            if (!RB::min_prep)
                time_wait_rb = cur_time;
        }
        if (cur_time == time_wait_rb)
            release_waiting_rb(cur_time);

        if (cur_time == time_busy_or)
        {
            release_pat_or(cur_time, waiting_rb);
            if (!OR::min_prep)
                time_free_or = cur_time;
            /*if (!Pat::min_transport)
                time_patient_waiting_rb = cur_time;*/
        }
        if (cur_time == time_free_or)
            assign_pat_or(cur_time, pat_q);

        /*if (cur_time == time_busy_rb)
        {
            release_pat_rb(cur_time, healed_q);
            if (!RB::min_prep)
                time_wait_rb = cur_time;
        }
        if (cur_time == time_wait_rb)
            release_waiting_rb(cur_time);
            */

        // since the following function is done is function release_pat_or, we need to move release_waiting_rb on top
        /*if (cur_time == time_patient_waiting_rb)
            assign_pat_rb(cur_time+Pat::min_transport, waiting_rb);
            */

    }
    int last_time = patients[healed_q.back()].RB_start + patients[healed_q.back()].min_recovery;

    print_res(last_time);
    }

    return 0;
}

void print_res(int lastt)
{
    string leading_spaces;
    int width;
    if (num_pat < 100)
    {
        width = 2;
        leading_spaces = " ";
    }
    else
    {
        width = 3;
        leading_spaces = "  ";
    }
    cout << leading_spaces << "Patient          Operating Room          Recovery Room\n"
         << leading_spaces << "#  Name     Room#  Begin   End      Bed#  Begin    End\n"
         << leading_spaces << "------------------------------------------------------\n";

    for (auto i = 0; i < num_pat; ++i)
    {
        const Pat &p = patients[i];

        int ostart_min = p.OR_start, oend_min = p.OR_start + p.min_surgery;
        int rstart_min = p.RB_start, rend_min = p.RB_start + p.min_recovery;

        cout << setw(width) << i+1 << "  " << setw(9) << left << p.lname << setw(3) << right << p.OR_i+1
             << "   " << setw(2) << ostart_min/60+st_hour << ":" << setw(2) << setfill('0') << ostart_min%60 << setfill(' ')
             << "   " << setw(2) << oend_min/60+st_hour << ":" << setw(2) << setfill('0') << oend_min%60 << setfill(' ')
             << "     " << setw(2) << p.RB_i+1
             << "   " << setw(2) << rstart_min/60+st_hour << ":" << setw(2) << setfill('0') << rstart_min%60 << setfill(' ')
             << "   " << setw(2) << rend_min/60+st_hour << ":" << setw(2) << setfill('0') << rend_min%60 << setfill(' ')
             << "\n";
    }
    cout << "\n";

    cout << "Facility Utilization\n"
         << "Type  # Minutes  % Used\n"
         << "-------------------------\n";

    for (auto i = 0; i < num_or; ++i)
        cout << "Room " << setw(2) << i+1 << setw(8) << orooms[i].total_mins << "   " << setw(5) << fixed << setprecision(2) << static_cast<double>(100*orooms[i].total_mins)/lastt << "\n";

    for (auto i = 0; i < num_rb; ++i)
        cout << "Bed  " << setw(2) << i+1 << setw(8) << rbeds[i].total_mins << "   " << setw(5) << fixed << setprecision(2) << static_cast<double>(100*rbeds[i].total_mins)/lastt << "\n";

    cout << "\n";
}
