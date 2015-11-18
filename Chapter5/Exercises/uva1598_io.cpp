// Exchange, ACM/ICPC NEERC 2006, UVa1598

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

struct Cmd {
    int size;
    int price;
    char type;
};

constexpr int MAXN = 10010;
map<int, set<int>> buy_pric2seq;
map<int, set<int>> sell_pric2seq;
map<int, int> pric2ttsize;
vector<Cmd> cmds(MAXN);

void try_trade(char t)
{
    while (!buy_pric2seq.empty() && !sell_pric2seq.empty())
    {
        auto cur_buy = --buy_pric2seq.end();
        auto cur_sell = sell_pric2seq.begin();
        int buy_price = cur_buy->first;
        int sell_price = cur_sell->first;
        auto &bqueue = cur_buy->second;
        auto &squeue = cur_sell->second;
        if (buy_price >= sell_price)
        {
            bool at_cur_price_ok = true;
            while (at_cur_price_ok)
            {
                auto bid = bqueue.begin();
                auto sid = squeue.begin();
                int trade_price = t == 'B'? sell_price : buy_price;
                int trade_size = min(cmds[*bid].size, cmds[*sid].size);
                cout << "TRADE " << trade_size << " " << trade_price << '\n';
                cmds[*bid].size -= trade_size, cmds[*sid].size -= trade_size;
                pric2ttsize[trade_price] -= trade_size;
                if (t == 'B')
                {
                    pric2ttsize[buy_price] -= trade_size;
                }
                else
                    pric2ttsize[sell_price] -= trade_size;

                if (!cmds[*bid].size)   // buy order is eaten
                    bqueue.erase(bid);
                if (!cmds[*sid].size)
                    squeue.erase(sid);
                if (bqueue.empty())
                {
                    buy_pric2seq.erase(cur_buy);
                    at_cur_price_ok = false;
                }
                if (squeue.empty())
                {
                    sell_pric2seq.erase(cur_sell);
                    at_cur_price_ok = false;
                }
            }
        }
        else
            return;
    }
}
void print()
{
    int bid_price =0, bid_size = 0, ask_price = 99999, ask_size = 0;
    if (!buy_pric2seq.empty())
    {
        bid_price = buy_pric2seq.rbegin()->first;
        bid_size = pric2ttsize[bid_price];
    }
    if (!sell_pric2seq.empty())
    {
        ask_price = sell_pric2seq.begin()->first;
        ask_size = pric2ttsize[ask_price];
    }

    cout << "QUOTE " << bid_size << ' ' << bid_price << " - "
                     << ask_size << ' ' << ask_price << '\n';
}
int main()
{
    ios_base::sync_with_stdio(false);
    bool first = true;
    int n;
    while (cin >> n)
    {
        if (first)  first = false;
        else    cout << '\n';
        // cmds.resize(n);
        for (auto i = 0; i < n; ++i)
        {
            string s; cin >> s;
            int arg1, arg2;
            if (s[0] == 'C')
            {
                cin >> arg1;
                --arg1;
            }
            else
                cin >> arg1 >> arg2;
            cmds[i].size = arg1;
            cmds[i].price = arg2;
            cmds[i].type = s[0];
        }

        for (auto i = 0; i < n; ++i)
        {
            Cmd &c = cmds[i];
            if (c.type == 'C')
            {
                auto &ccmd = cmds[c.size];
                if (ccmd.size)
                {
                    // int erased = 0;
                    if (ccmd.type == 'B')
                    {
                        buy_pric2seq[ccmd.price].erase(c.size);
                        if (buy_pric2seq[ccmd.price].empty())
                            buy_pric2seq.erase(ccmd.price);
                    }
                    else
                    {
                        sell_pric2seq[ccmd.price].erase(c.size);
                        if (sell_pric2seq[ccmd.price].empty())
                            sell_pric2seq.erase(ccmd.price);
                    }

                    // if (erased)
                        pric2ttsize[ccmd.price] -= ccmd.size;
                        ccmd.size = 0;
                }
            }
            else
            {
                pric2ttsize[c.price] += c.size;
                set<int> *sp;
                if (c.type == 'B')
                    sp = &buy_pric2seq[c.price];
                else
                    sp = &sell_pric2seq[c.price];
                sp->insert(sp->end(), i);
                try_trade(c.type);
            }
            print();
        }

        // clear up
        buy_pric2seq.clear();
        sell_pric2seq.clear();
        pric2ttsize.clear();
        // cmds.clear();
    }

    return 0;
}
