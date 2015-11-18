// Use of Hospital Facilities, ACM/ICPC World Finals 1991, UVa212
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <cassert>
using namespace std;

// Operating room
struct OR {
    static int min_prep;
    int patient = -1;
    int total_mins = 0;
    int end_time = 0;
    bool working = false;
} orooms[12];
int OR::min_prep;

// Recovery Bed
struct RB {
    static int min_prep;
    int patient = -1;
    int total_mins = 0;
    int end_time = 0;
    bool working = false;
} rbeds[32];
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
    Pat() = default;
    Pat(string &&s, int min_s, int min_r): lname(std::move(s)), min_surgery(min_s), min_recovery(min_r)
    {}
} patients[2048];
int Pat::min_transport;
// vector<Pat> patients;
int st_hour, num_or, num_rb, mins_transport, num_pat;

// Function Prototypes
void print_res(int lastt);
void c_print(int lastt);

int main()
{
    // ios_base::sync_with_stdio(false);
    while (cin >> num_or >> num_rb >> st_hour >> Pat::min_transport >> OR::min_prep >> RB::min_prep >> num_pat)
    {
        for (auto i = 0; i < num_or; ++i)
            orooms[i] = OR();
        for (auto i = 0; i < num_rb; ++i)
            rbeds[i] = RB();
        for (auto i = 0; i < num_pat; ++i)
        {
            string lname; int min_s, min_r;
            cin >> lname >> min_s >> min_r;
            patients[i] = Pat(std::move(lname), min_s, min_r);
            // patients.emplace_back(std::move(lname), min_s, min_r);
        }

        // Start Simulation
        queue<int> healed_q;

        int pid = 0;
        set<int> timeline {0};
        while (!timeline.empty())
        {
            int cur_time = *timeline.begin();
            timeline.erase(timeline.begin());
            // if there is patient in OR and end time is reached, release patient to waiting_rb queue
            vector<int> A2B;
            for (auto i = 0; i < num_or; ++i)
            {
                if (orooms[i].working && orooms[i].end_time <= cur_time)
                {
                    orooms[i].working = false;
                    if (orooms[i].patient >= 0)
                    {
                        A2B.push_back(orooms[i].patient);
                        orooms[i].working = true;
                        orooms[i].end_time = cur_time + OR::min_prep;
                        orooms[i].patient = -1;
                        timeline.insert(orooms[i].end_time);
                    }
                }
            }

            // if there is patient in recovery bed, and the end time is reached, release patient to healed_q queue
            for (auto i = 0; i < num_rb; ++i)
            {
                if (rbeds[i].working && rbeds[i].end_time <= cur_time)
                {
                    rbeds[i].working = false;
                    if (rbeds[i].patient >= 0)
                    {
                        healed_q.push(rbeds[i].patient);
                        rbeds[i].working = true;
                        rbeds[i].end_time = cur_time + RB::min_prep;
                        rbeds[i].patient = -1;
                        timeline.insert(rbeds[i].end_time);
                    }
                }
            }

            // assign patients to recovery beds now (only beds currently available is considered, even though it takes time to transport patients and by the time they arrive other beds may become available
            for (int i = 0; i < A2B.size(); ++i)
            {
                int pat = A2B[i];
                for (auto i = 0; i < num_rb; ++i)
                {
                    if (rbeds[i].working == false) // currently available bed found
                    {
                        rbeds[i].working = true;
                        rbeds[i].patient = pat;
                        rbeds[i].end_time = cur_time + Pat::min_transport + patients[pat].min_recovery;
                        rbeds[i].total_mins += patients[pat].min_recovery;
                        timeline.insert(rbeds[i].end_time);

                        assert(patients[pat].RB_i == -1 && patients[pat].RB_start == -1);
                        patients[pat].RB_i = i;
                        patients[pat].RB_start = cur_time + Pat::min_transport;
                        break;
                    }
                }
            }

            // assign patients to OR now
            for ( ; pid < num_pat; ++pid)
            {
                int ok = 0;
                for (auto i = 0; i < num_or; ++i)
                {
                    if (orooms[i].working == false)
                    {
                        orooms[i].working = true;
                        orooms[i].patient = pid;
                        orooms[i].end_time = cur_time + patients[pid].min_surgery;
                        orooms[i].total_mins += patients[pid].min_surgery;
                        timeline.insert(orooms[i].end_time);

                        assert(patients[pid].OR_i == -1 && patients[pid].OR_start == -1);
                        patients[pid].OR_i = i;
                        patients[pid].OR_start = cur_time;
                        ok = 1;
                        break;
                    }
                }
                if (!ok)
                    break;
            }
        }
        int last_time = patients[healed_q.back()].RB_start + patients[healed_q.back()].min_recovery;

        print_res(last_time);
        // c_print(last_time);
    }

    return 0;
}

void c_print(int lastt)
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
}


void print_res(int lastt)
{
    string leading_spaces;
    int width;
    if (num_pat < 10)
    {
        width = 2;
        leading_spaces = "";
    }
    else if (num_pat < 100)
    {
        width = 2;
        leading_spaces = " ";
    }
    else
    {
        width = 3;
        leading_spaces = "  ";
    }
    leading_spaces = " ";
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
