// 10-20-30, ACM/ICPC World Finals 1996, UVa 246
// http://morris821028.github.io/2014/07/02/oj/uva/uva-246/ (good idea with flattening all the cards into a state)
// http://blog.csdn.net/acm_hkbu/article/details/41823449 (use vector and deque's own lexicographically comparison)
// http://blog.csdn.net/accelerator_/article/details/38156965
// http://xwk.iteye.com/blog/2130572

#include <iostream>
#include <deque>
#include <set>
#include <cstring>
#include <tuple>
using namespace std;

using pile = deque<int>;
pile board[7];
pile hand;
int dealt;
constexpr int impossible = -1;

struct State
{
    int all_cards[64];
    State()
    {
        memset(all_cards, 0, sizeof(all_cards));
        int count = 0;
        for (auto &b: board)
        {
            for (auto c: b)
                all_cards[count++] = c;
            all_cards[count++] = impossible;
        }
        for (auto &c: hand)
            all_cards[count++] = c;
        all_cards[count++] = impossible;
    }
    bool operator< (const State &s) const
    {
        return memcmp(all_cards, s.all_cards, sizeof(all_cards)) < 0;
    }
};

set<State> pasts;

void check3(int i);
void deal()
{
    for (auto i = 0; i < 7; ++i)
    {
        int card = hand.front();
        hand.pop_front();
        board[i].push_back(card);
    }
}

void play()
{
    while (1)
    {
        bool end = false;
        for (auto i = 0; i < 7; ++i)
        {
            if (board[i].empty())
                continue;
            int card = hand.front();
            hand.pop_front();
            board[i].push_back(card);
            dealt++;
            check3(i);
            if (hand.size() == 0) // lose
            {
                cout << "Loss: " << dealt << "\n";
                end = true;
                break;
            }
            if (hand.size() == 52)
            {
                cout << "Win : " << dealt << "\n";
                end = true;
                break;
            }
            bool no_dup = true;
            std::tie(std::ignore, no_dup) = pasts.insert(State());
            if (!no_dup)
            {
                cout << "Draw: " << dealt << "\n";
                end = true;
                break;
            }
        }
        if (end)
            return;
    }
}

void check3(int i)
{
    pile &cur = board[i];
    while (cur.size() >= 3)
    {
        auto N = cur.size();
        int val1 = cur[0] + cur[1] + cur[N-1];
        int val2 = cur[0] + cur[N-2] + cur[N-1];
        int val3 = cur[N-3] + cur[N-2] + cur[N-1];
        if (val1 % 10 == 0) // == 10, 20, or 30
        {
            hand.push_back(cur.front()); cur.pop_front();
            hand.push_back(cur.front()); cur.pop_front();
            hand.push_back(cur.back()); cur.pop_back();
        }
        // auto newsize = cur.size();
        else if (val2 % 10 == 0)
        {
            hand.push_back(cur.front());
            hand.push_back(cur[N-2]);
            hand.push_back(cur.back());
            cur.pop_front(); cur.pop_back(); cur.pop_back();
        }
        else if (val3 % 10 == 0)
        {
            hand.push_back(cur[N-3]);
            hand.push_back(cur[N-2]);
            hand.push_back(cur[N-1]);
            cur.pop_back(); cur.pop_back(); cur.pop_back();
        }
        else
            return;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    while (1)
    {
        int v; cin >> v;
        if (!v) return 0;
        hand.push_back(v);
        for (auto i = 1; i < 52; ++i)
        {
            cin >> v; hand.push_back(v);
        }

        deal(); pasts.insert(State());
        deal(); pasts.insert(State());
        dealt = 14;

        play();

        hand.clear();
        for (auto &b: board)
            b.clear();
        pasts.clear();
    }

    return 0;
}
