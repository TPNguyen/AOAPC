#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct tired_stdn
{
    int awake_len, sleep_len;
    // bool is_sleeping(int time) const { return time > awake_len; }
    bool is_awake(int time) const { return time <= awake_len; }
    bool is_about_to_sleep(int time) const  { return time == awake_len; }
    bool is_about_to_wakeup(int time) const { return time == sleep_len + awake_len; }
};

template<typename f>
int nums(const vector<int> &stat, const vector<tired_stdn> &students, f func);

vector<int> get_next_status(const vector<int> &stat, const vector<tired_stdn> &students, bool more_awake);

int main()
{
    int num_students;
    int kase = 0;
    while (cin >> num_students && num_students)
    {
        ++kase;
        vector<tired_stdn> students(num_students);
        vector<int> status(num_students);

        for (auto i = 0; i < num_students; ++i)
            cin >> students[i].awake_len >> students[i].sleep_len >> status[i];

        // transform(students.begin(), students.end(), status.begin(), [](const tired_stdn &ts) { return ts.init; });

        set<vector<int>> progression {status};
        int time = 1;
        while (true)
        {
            int num_awake_students;
            if ( (num_awake_students = nums(status, students, &tired_stdn::is_awake)) == num_students)
            {
                // found = true; res = time;
                break;
            }
            // generate next time slot's status
            status = get_next_status(status, students, num_awake_students >= num_students-num_awake_students);
            ++time;
            if (progression.insert(status).second == false)
            {
                // no_solution = true;
                time = -1;
                break;
            }
        }

        cout << "Case " << kase << ": " << time << "\n";
    }

    return 0;
}

template<typename f>
int nums(const vector<int> &stat, const vector<tired_stdn> &students, f func)
{
    int count = 0;
    for (auto i = 0; i < stat.size(); ++i)
        if ((students[i].*func)(stat[i]))
            ++count;

    return count;
}

vector<int> get_next_status(const vector<int> &stat, const vector<tired_stdn> &students, bool more_awake)
{
    vector<int> ret;
    // na += nums(stat, students, &tired_stdn::is_about_to_wakeup);
    // bool more_awake = na >= num_students - na;

    for (auto i = 0; i < stat.size(); ++i)
    {
        int t;
        if (students[i].is_about_to_wakeup(stat[i]))
            t = 1;
        else if (students[i].is_about_to_sleep(stat[i]))
            t = more_awake? 1 : stat[i]+1;
        else // continue to be awake or sleeping
            t = stat[i] + 1;

        ret.push_back(t);
    }

    /*cout << "(";
    for (auto e: ret)
        cout << e << ",";
    cout << ")\n";*/

    return ret;
}

