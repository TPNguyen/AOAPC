// Use of Hospital Facilities, ACM/ICPC World Finals 1991, UVa212
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
using namespace std;

// Operating room
struct OR {
    static int min_prep;
    int patient = -1;
    int total_mins = 0;
    int next_avai_time = 0;
    int end_time = 0;
};
int OR::min_prep;

// Recovery Bed
struct RB {
    static int min_prep;
    int patient = -1;
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
    int OR_start = -1;
    int RB_i = -1;
    int RB_start = -1;
    Pat(string &&s, int min_s, int min_r): lname(std::move(s)), min_surgery(min_s), min_recovery(min_r)
    {}
};
int Pat::min_transport;
int st_hour, num_or, num_rb, mins_transport, num_pat;

// Function Prototypes
void print_res(int lastt, const vector<OR> &orooms, const vector<RB> &rbeds, const vector<Pat> &patients);
// void c_print(int lastt);

int main()
{
    ios_base::sync_with_stdio(false);
    while (cin >> num_or >> num_rb >> st_hour >> Pat::min_transport >> OR::min_prep >> RB::min_prep >> num_pat) {
        vector<OR> orooms(num_or);
        vector<RB> rbeds(num_rb);
        vector<Pat> patients;
    for (auto i = 0; i < num_pat; ++i)
    {
        string lname; int min_s, min_r;
        cin >> lname >> min_s >> min_r;
        patients.emplace_back(std::move(lname), min_s, min_r);
    }

    // Start Simulation
    queue<int> pat_q;
    for (auto i = 0; i < num_pat; ++i)
        pat_q.push(i);
    queue<int> healed_q;
    queue<int> waiting_rb;
    set<int> timeline {0};
    int last_out;
    while (!timeline.empty())
    {
        int cur_time = *timeline.begin();
        timeline.erase(timeline.begin());
        // if there is patient in OR and end time is reached, release patient to waiting_rb queue
        for (auto i = 0; i < num_or; ++i)
        {
            if (orooms[i].patient >= 0 && orooms[i].end_time <= cur_time)
            {
                waiting_rb.push(orooms[i].patient);
                orooms[i].patient = -1;
            }
        }

        // if there is patient in recovery bed, and the end time is reached, release patient to healed_q queue
        for (auto i = 0; i < num_rb; ++i)
        {
            if (rbeds[i].patient >= 0 && rbeds[i].end_time <= cur_time)
            {
                healed_q.push(rbeds[i].patient);
                last_out = rbeds[i].patient;
                rbeds[i].patient = -1;
            }
        }

        // assign patients to recovery beds now (only beds currently available is considered, even though it takes time to transport patients and by the time they arrive other beds may become available
        while (!waiting_rb.empty())
        {
            int pat = waiting_rb.front();
            waiting_rb.pop();
            for (auto i = 0; i < num_rb; ++i)
            {
                if (rbeds[i].next_avai_time <= cur_time) // currently available bed found
                {
                    rbeds[i].patient = pat;
                    rbeds[i].end_time = cur_time + Pat::min_transport + patients[pat].min_recovery;
                    rbeds[i].next_avai_time = rbeds[i].end_time + RB::min_prep;
                    rbeds[i].total_mins += patients[pat].min_recovery;
                    timeline.insert(rbeds[i].end_time);
                    // timeline.insert(rbeds[i].next_avai_time); // not sure if we need this??

                    patients[pat].RB_i = i;
                    patients[pat].RB_start = cur_time + Pat::min_transport;
                    break;
                }
            }
        }

        // assign patients to OR now
        while (!pat_q.empty())
        {
            int pat = pat_q.front();
            int i = 0;
            for (; i < num_or; ++i)
            {
                if (orooms[i].next_avai_time <= cur_time)
                {
                    orooms[i].patient = pat;
                    orooms[i].end_time = cur_time + patients[pat].min_surgery;
                    orooms[i].next_avai_time = orooms[i].end_time + OR::min_prep;
                    orooms[i].total_mins += patients[pat].min_surgery;
                    timeline.insert(orooms[i].end_time);
                    timeline.insert(orooms[i].next_avai_time);

                    patients[pat].OR_i = i;
                    patients[pat].OR_start = cur_time;
                    break;
                }
            }
            if (i == num_or)
                break;
            else
                pat_q.pop();
        }
    }
    int last_time = patients[healed_q.back()].RB_start + patients[healed_q.back()].min_recovery;

    print_res(last_time, orooms, rbeds, patients);
    // c_print(last_time);

    }
    return 0;
}

void print_res(int lastt, const vector<OR> &orooms, const vector<RB> &rbeds, const vector<Pat> &patients)
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

/*void c_print(int lastt)
{
    puts(" Patient          Operating Room          Recovery Room");
    puts(" #  Name     Room#  Begin   End      Bed#  Begin    End");
    puts(" ------------------------------------------------------");
    for (int i = 0; i < num_pat; i++) {
        const Pat &p = patients[i];

        int ostart_min = p.OR_start, oend_min = p.OR_start + p.min_surgery;
        int rstart_min = p.RB_start, rend_min = p.RB_start + p.min_recovery;
        printf("%2d  %-9s %2d  %3d:%02d  %3d:%02d    %3d  %3d:%02d  %3d:%02d\n",
                i+1, p.lname.data(), p.OR_i+1,
                ostart_min/60+st_hour, ostart_min%60, oend_min/60+st_hour, oend_min%60, p.RB_i+1,
                rstart_min/60+st_hour, rstart_min%60, rend_min/60+st_hour, rend_min%60);
    }
    puts("");
    puts("Facility Utilization");
    puts("Type  # Minutes  % Used");
    puts("-------------------------");
    for (int i = 0; i < num_or; i++) {
        printf("%-4s %2d %7d %7.2lf\n", "Room", i+1, orooms[i].total_mins, (double) orooms[i].total_mins*100/lastt);
    }
    for (int i = 0; i < num_rb; i++) {
        printf("%-4s %2d %7d %7.2lf\n", "Bed", i+1, rbeds[i].total_mins, (double) rbeds[i].total_mins*100/lastt);
    }
    puts("");
}*/

