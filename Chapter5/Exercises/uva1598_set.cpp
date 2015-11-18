// Exchange, ACM/ICPC NEERC 2006, UVa1598

#include <iostream>
#include <string>
#include <set>
using namespace std;

struct buy_order {
    int price;
    mutable int size;
    int seq;
};
bool operator< (const buy_order &o1, const buy_order &o2)
{
    return o1.price > o2.price;
}
struct sell_order {
    int price;
    mutable int size;
    int seq;
};
bool operator< (const sell_order &o1, const sell_order &o2)
{
    return o1.price < o2.price;
}

bool can_trade(int bp, const multiset<sell_order>::iterator &so)
{
    return bp >= so->price;
}
bool can_trade(int sp, const multiset<buy_order>::const_iterator &bo)
{
    return bo->price >= sp;
}

void print_quote(multiset<buy_order> &bos, multiset<sell_order> &sos)
{
    int bid_size = 0, bid_price = 0;
    if (!bos.empty())
    {
        bid_price = bos.begin()->price;
        auto pit = bos.equal_range(*bos.begin());
        for (auto it = pit.first; it != pit.second; ++it)
            bid_size += it->size;
    }
    int ask_size = 0, ask_price = 99999;
    if (!sos.empty())
    {
        ask_price = sos.begin()->price;
        auto pit = sos.equal_range(*sos.begin());
        for (auto it = pit.first; it != pit.second; ++it)
            ask_size += it->size;
    }

    cout << "QUOTE " << bid_size << ' ' << bid_price << " - "
                     << ask_size << ' ' << ask_price << '\n';
}
void print_quote(multiset<sell_order> &sos, multiset<buy_order> &bos)
{
    print_quote(bos, sos);
}

template <typename IN, typename WAIT>
void process_incoming(multiset<IN> &incoming, multiset<WAIT> &waiting, int seq)
{
    int size, price;
    cin >> size >> price;
    auto top_waiting = waiting.begin();
    if (can_trade(price, top_waiting))
    {
        for ( ; size && top_waiting != waiting.end(); ++top_waiting)
        {
            int trade_price = top_waiting->price;
            int trade_size = min(top_waiting->size, size);
            cout << "TRADE " << trade_size << " " << trade_price << '\n';
            size -= trade_size;
            top_waiting->size -= trade_size;
            if (top_waiting->size)
                break;
        }
        waiting.erase(waiting.begin(), top_waiting);
    }
    if (size)
    {
        auto it = incoming.upper_bound(*incoming.begin());
        incoming.insert(it, {price, size, seq});
    }

    print_quote (incoming, waiting);
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
        multiset<buy_order> buy_orders;
        multiset<sell_order> sell_orders;
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
                bool found = false;
                for (auto it = buy_orders.begin(); it != buy_orders.end(); ++it)
                    if (it->seq == ci)
                    {
                        found = true;
                        buy_orders.erase(it);
                        break;
                    }
                if (!found)
                {
                    for (auto it = sell_orders.begin(); it != sell_orders.end(); ++it)
                        if (it->seq == ci)
                        {
                            sell_orders.erase(it);
                            break;
                        }
                }
                print_quote(buy_orders, sell_orders);
            }
        }
    }

    return 0;
}


