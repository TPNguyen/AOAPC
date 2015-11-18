// PGA Tour Prize Money, Uva207
// ranking : as long as one doesn't get DQ; only ones that get money has possible tie indicator
// money : amateur and out of top 70 players don't have money. so in a sense, professional who gets no money is like an amateur

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <sstream>
#include <iomanip>
using namespace std;

constexpr int MAXP = 150;
constexpr int NUM_PERCENT = 70;
constexpr int MAX_SCORE = 1E5;
struct Golfer
{
    string name;
    vector<int> scores;
    double money = 0.0;
    int f2r_score = 0, total_score = 0, dq_num = 0, rank = 0;
    bool is_amateur = false, is_tie = false;

    Golfer() : scores(4, MAX_SCORE){}
};

using PGAit = vector<Golfer>::const_iterator;
void print_ans(PGAit b, PGAit dq, PGAit cutoff);

// Static Data
namespace {

    double total_prize;
    array<double, NUM_PERCENT> purse;
    vector<Golfer> players;
    int numplayers;
}

void init()
{
    cin >> total_prize;
    for (auto i = 0; i < NUM_PERCENT; ++i)
    {
        cin >> purse[i];
        purse[i] *= total_prize/100.0;
    }
    cin >> numplayers;
    players = vector<Golfer> (numplayers);

    cin.ignore(100, '\n');
    // read in player info
    for (auto i = 0; i < numplayers; ++i)
    {
        string p;
        getline(cin, p);

        players[i].name = p.substr(0, 20);
        if (players[i].name.find('*') != string::npos)
            players[i].is_amateur = true;

        istringstream iss (p.substr(20));
        for (auto is = 0; is < 4; ++is)
        {
            string score; iss >> score;
            if (score == "DQ")
            {
                players[i].dq_num = 4-is;
                break;
            }
            players[i].scores[is] = stoi(score);

            if (is < 2) players[i].f2r_score += players[i].scores[is];
            players[i].total_score += players[i].scores[is];
        }
    }
}

void process()
{
    // find who made the cut (first 70 positions)
    const auto it_begin = players.begin();
    auto it = partition(it_begin, it_begin+numplayers, [](const Golfer &a) { return a.dq_num <= 2; });
    auto it_cutoff = it;
    if (distance(it_begin, it) > 70)
    {
        auto comp = [](const Golfer &a, const Golfer &b) { return a.f2r_score < b.f2r_score; };
        sort(it_begin, it, comp);
        auto last_candidate = it_begin + 69;
        it_cutoff = upper_bound(last_candidate, it, *last_candidate, comp);
    }

    // find non-DQ and DQ players
    it = partition(it_begin, it_cutoff, [](const Golfer &a) { return a.dq_num == 0; });
    sort(it_begin, it, [](const Golfer &a, const Golfer &b) -> bool
            {
              return a.total_score < b.total_score || (a.total_score == b.total_score && a.name < b.name);
              }
        );
    sort(it, it_cutoff, [](const Golfer &a, const Golfer &b) -> bool 
            {
                if (a.dq_num != b.dq_num) return a.dq_num < b.dq_num;
                else if (a.total_score != b.total_score) return a.total_score < b.total_score;
                else return a.name < b.name;
            }
        );

    auto next_prize_position = purse.begin();
    for (auto next_player = it_begin; next_player < it; )
    {
        int ranking = distance(it_begin, next_player) + 1;
        auto cur_total_score = next_player->total_score;
        if (next_prize_position != purse.end())
        {
            // Still have non-DQ'ed player with prize money
            // Calculate how way ties there are
            double money_earned = 0.0;
            auto i = next_player;
            auto num_prof = 0;
            for (; i < it && i->total_score == cur_total_score; ++i)
            {
                if (!i->is_amateur)
                {
                    ++num_prof;
                    if (next_prize_position != purse.end())
                        money_earned += *next_prize_position++;
                }
            }
            if (num_prof)
                money_earned /= num_prof;

            for ( ; next_player != i; ++next_player)
            {
                next_player->rank = ranking;
                if (!next_player->is_amateur)
                {
                    next_player->money = money_earned;
                    next_player->is_tie = num_prof > 1;
                }
            }
        }
        else
        {

            // professional player but doesn't earn any money. such an amateur
            auto i = next_player;
            for (; i < it && i->total_score == cur_total_score; ++i)
                ;
            for ( ; next_player != i; ++next_player)
            {
                next_player->rank = ranking;
                next_player->is_amateur = true;
            }
        }
    }

    print_ans(it_begin, it, it_cutoff);
}

void print_ans(PGAit b, PGAit dq, PGAit cutoff)
{
    cout << "Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n";
    cout << "-----------------------------------------------------------------------\n";
    for (auto i = b ; i != cutoff; ++i)
    {
        cout << left;
        cout << setw(21) << i->name ;
        // ranking
        string ranking;
        if (i < dq)
        {
            ranking = to_string(i->rank);
            if (i->is_tie) ranking += 'T';
        }
        else
            ranking = "";
        cout << setw(10) << ranking;

        // scores
        for (auto is = 0; is < 4-i->dq_num; ++is)
            cout << setw(5) << i->scores[is];
        for (auto idq = 0; idq < i->dq_num; ++idq)
            cout << setw(5) << "";

        if (i->dq_num)
            cout << "DQ";
        else if (i->is_amateur)
            cout << i->total_score;
        else
        {
            cout << setw(10) << i->total_score;
            cout << '$' << setw(9) << right << fixed << setprecision(2) << i->money;
        }
        cout << "\n";
    }
}


int main()
{
    ios_base::sync_with_stdio(false);

    int num_cases; cin >> num_cases;
    while (num_cases--)
    {

        init();
        process();

        if (num_cases)
            cout << "\n";
    }

    return 0;
}

