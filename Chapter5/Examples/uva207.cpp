// PGA Tour Prize Money, Uva207

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Golfer
{
    string name;
    vector<int> scores;
    int f2r_score, total_score;
    bool is_amateur, is_DQ;
    Golfer() : scores(4){}
};

int main()
{
    ios_base::sync_with_stdio(false);

    constexpr double eps = 1e-3;
    double total_prize = 0.0;
    array<double, 70> purse;
    array<Golfer, 144> players;
    int num_cases; cin >> num_cases;
    while (num_cases--)
    {
        cin >> total_prize;
        for (auto i = 0; i < 70; ++i)
        {
            cin >> purse[i];
            purse[i] *= total_prize/100.0;
        }

        int numplayers; cin >> numplayers;
        cin.ignore(100, '\n');
        // read in player info
        for (auto i = 0; i < numplayers; ++i)
        {
            string p;
            getline(cin, p);

            auto fullname = p.substr(0,20);
            auto ln_end = fullname.size()-1;
            while (isblank(fullname[ln_end]))
                --ln_end;
            players[i].name = fullname.substr(0, ln_end+1);
            istringstream iss (p.substr(20));
            auto is = 0;
            for (; is < 4; ++is)
            {
                string score; iss >> score;
                if (score == "DQ")
                    break;
                players[i].scores[is] = stoi(score);
            }
            for (; is < 4; ++is)
                players[i].scores[is] = 1000;

            players[i].is_amateur = players[i].name.back() == '*';
            players[i].f2r_score = players[i].scores[0] + players[i].scores[1];
            players[i].total_score = players[i].scores[0] + players[i].scores[1] + players[i].scores[2] + players[i].scores[3];
            players[i].is_DQ = players[i].total_score > 1000;
        }

        // find who made the cut (first 70 positions)
        sort(players.begin(), players.begin()+numplayers, [](const Golfer &a, const Golfer &b) { return a.f2r_score < b.f2r_score; });

        int num_in_cutoff = distance(players.begin(), lower_bound(players.begin(), players.begin()+numplayers, 1000, [] (const Golfer& a, const int b) { return a.f2r_score < b; }));
        if (num_in_cutoff > 70)
        {
            auto f2r_score = players[69].f2r_score;
            num_in_cutoff = 70;
            while (players[num_in_cutoff].f2r_score == f2r_score)
                ++num_in_cutoff;
        }

        // sort based on total score, then by name
        sort(players.begin(), players.begin()+num_in_cutoff, [](const Golfer &a, const Golfer &b) { return a.total_score < b.total_score || (a.total_score == b.total_score && a.name < b.name); });

        // output
        cout << "Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n";
        cout << "-----------------------------------------------------------------------\n";
        auto next_player = 0;
        auto next_prize_position = 0;
        while (next_player < num_in_cutoff)
        {
            // all remaining players are either DQ'ed or don't receive any prize money
            if (players[next_player].is_DQ || next_prize_position >= 70)
                break;

            // Still have non-DQ'ed player with prize money
            // Calculate how way ties there are
            double money_earned = 0.0;
            auto cur_total_score = players[next_player].total_score;
            auto i = next_player, num_prof = 0;
            for (; i < num_in_cutoff && players[i].total_score == cur_total_score; ++i)
            {
                if (!players[i].is_amateur)
                {
                    ++num_prof;
                    if (next_prize_position < 70)
                        money_earned += purse[next_prize_position++];
                }
            }

            string ranking = to_string(next_player+1);
            string prof_ranking = ranking;
            if (num_prof)
            {
                // percentage /= num_prof;
                money_earned /= num_prof;
                // money_earned += eps;
                // money_earned = round(money_earned) / 100;
                if (num_prof > 1)
                    prof_ranking += 'T';
            }

            for (auto j = next_player; j < i; ++j)
            {
                cout << left;
                cout << setw(21) << players[j].name 
                     << setw(10) << (players[j].is_amateur? ranking : prof_ranking)
                     << setw(5) << players[j].scores[0]
                     << setw(5) << players[j].scores[1]
                     << setw(5) << players[j].scores[2]
                     << setw(5) << players[j].scores[3]
                     << setw(players[j].is_amateur? 0: 10) << players[j].total_score;
                if (!players[j].is_amateur)
                    cout << '$' << setw(9) << right << fixed << setprecision(2) << money_earned;
                cout << "\n";
            }

            // update
            next_player = i;
        }
        for (auto j = next_player; j < num_in_cutoff; ++j)
        {
            cout << left;
            cout << setw(21) << players[j].name
                 << setw(10) << (players[j].is_DQ? "" : to_string(j+1));
            auto is = 0, iDQ = 4 - players[j].total_score/1000;
            for (; is < iDQ; ++is)
                 cout << setw(5) << players[j].scores[is];
            for (; is < 4; ++is)
                 cout << setw(5) << "";

            if (players[j].is_DQ)
                cout << "DQ";
            else
                cout << players[j].total_score;
            cout << "\n";
        }

        if (num_cases)
            cout << "\n";
    }

    return 0;
}
