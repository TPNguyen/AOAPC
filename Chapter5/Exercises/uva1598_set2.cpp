// Exchange, ACM/ICPC NEERC 2006, UVa1598

#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <utility>
#include <unordered_set>
using namespace std;

struct order {
    int price;
    int seq;
    mutable int size;
};

auto buy_cmp = [](const order &o1, const order &o2) -> bool
{
    if (o1.price != o2.price)
        return o1.price > o2.price;
    return o1.seq < o2.seq;
};
auto sell_cmp = [](const order &o1, const order &o2) -> bool
{
    if (o1.price != o2.price)
        return o1.price < o2.price;
    return o1.seq < o2.seq;
};
using Buys = multiset<order, decltype(buy_cmp)>;
using Sells = multiset<order, decltype(sell_cmp)>;

unordered_map<int, int> price2size;
unordered_map<int, Buys::iterator> b_seq2iter;
unordered_map<int, Sells::iterator> s_seq2iter;
unordered_set<int> gone;

///////////////////////////////////////////////////////////////////////////
template<typename T>
bool can_trade(int bp, const Sells::iterator &so, const T&)
{
    return bp >= so->price;
}
template<>
bool can_trade<Buys>(int sp, const Buys::iterator &bo, const Buys&)
{
    return bo->price >= sp;
}

template<typename T>
void add_seq2iter_map(int seq, Buys::iterator &it, T*)
{
    b_seq2iter.insert({seq, it});
}
template<>
void add_seq2iter_map<Sells>(int seq, Buys::iterator &it, Sells*)
{
    s_seq2iter.insert({seq, it});
}

void print_quote(Buys &bos, Sells &sos)
{
    int bid_size = 0, bid_price = 0;
    if (!bos.empty())
    {
        bid_price = bos.begin()->price;
        bid_size = price2size[bid_price];
    }
    int ask_size = 0, ask_price = 99999;
    if (!sos.empty())
    {
        ask_price = sos.begin()->price;
        ask_size = price2size[ask_price];
    }

    cout << "QUOTE " << bid_size << ' ' << bid_price << " - "
                     << ask_size << ' ' << ask_price << '\n';
}

template <typename IN, typename WAIT>
void process_incoming(multiset<order, IN> &incoming, multiset<order, WAIT> &waiting, int seq)
{
    int size, price; cin >> size >> price;
    auto top_waiting = waiting.begin();
    for ( ; size && top_waiting != waiting.end(); ++top_waiting)
    {
        if (can_trade(price, top_waiting, waiting))
        {
            int trade_price = top_waiting->price;
            int trade_size = min(top_waiting->size, size);
            cout << "TRADE " << trade_size << " " << trade_price << '\n';
            size -= trade_size;
            top_waiting->size -= trade_size;

            price2size[trade_price] -= trade_size;
            if (!top_waiting->size)
                gone.insert(top_waiting->seq);
            else
                break;
        }
        else break;
    }
    waiting.erase(waiting.begin(), top_waiting);
    if (size)
    {
        auto p2s_pit = price2size.insert({price, size});
        if (!p2s_pit.second)
            p2s_pit.first->second += size;
        auto it = incoming.insert(incoming.begin(), {price, seq, size});
        add_seq2iter_map(seq, it, &incoming);
    }
    else
        gone.insert(seq);
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

        Buys buy_orders(buy_cmp);
        Sells sell_orders(sell_cmp);
        for (auto i = 1; i <= n; ++i)
        {
            string cmd; cin >> cmd;
            if (cmd[0] == 'B')
                process_incoming(buy_orders, sell_orders, i);
            else if (cmd[0] == 'S')
                process_incoming(sell_orders, buy_orders, i);
            else // cancel order
            {
                int ci; cin >> ci;
                if (!gone.count(ci))
                {
                    if (b_seq2iter.count(ci))
                    {
                        auto &it = b_seq2iter[ci];
                        price2size[it->price] -= it->size;
                        buy_orders.erase(it);
                    }
                    else
                    {
                        auto &it = s_seq2iter[ci];
                        price2size[it->price] -= it->size;
                        sell_orders.erase(it);
                    }
                    gone.insert(ci);
                }
            }
            print_quote(buy_orders, sell_orders);
        }
        price2size.clear();
        b_seq2iter.clear();
        s_seq2iter.clear();
        gone.clear();
    }

    return 0;
}
