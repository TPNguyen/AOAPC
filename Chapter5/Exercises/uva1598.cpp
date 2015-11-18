// Exchange, ACM/ICPC NEERC 2006, UVa1598

#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
using namespace std;

struct buy_order {
    int price;
    int size;
    int seq;
};
bool operator< (const buy_order &o1, const buy_order &o2)
{
    return o1.price < o2.price;
}
struct sell_order {
    int price;
    int size;
    int seq;
};
bool operator< (const sell_order &o1, const sell_order &o2)
{
    return o1.price > o2.price;
}

bool can_trade(int bp, const sell_order &so)
{
    return bp >= so.price;
}
bool can_trade(int sp, const buy_order &bo)
{
    return bo.price >= sp;
}

void print_quote(priority_queue<buy_order> &bos, priority_queue<sell_order> &sos, const unordered_set<int> &cancelled)
{
    int bid_size = 0, bid_price = 0;
    vector<buy_order> all_top_b;
    while (!bos.empty())
    {
        auto cur_top = bos.top();
        if (!cancelled.count(cur_top.seq))
        {
            if (bid_price == 0)
                bid_price = cur_top.price;
            else if (bid_price != cur_top.price)
                break;
            all_top_b.push_back(cur_top);
        }
        bos.pop();
    }
    for (const auto &bo: all_top_b)
    {
        bid_size += bo.size;
        bos.push(bo);
    }
    int ask_size = 0, ask_price = 0;
    vector<sell_order> all_top_s;
    while (!sos.empty())
    {
        auto cur_top = sos.top();
        if (!cancelled.count(cur_top.seq))
        {
            if (ask_price == 0)
                ask_price = cur_top.price;
            else if (ask_price != cur_top.price)
                break;
            all_top_s.push_back(cur_top);
        }
        sos.pop();
    }
    for (const auto &so: all_top_s)
    {
        ask_size += so.size;
        sos.push(so);
    }

    cout << "QUOTE " << bid_size << ' ' << bid_price << " - "
                     << ask_size << ' ' << (ask_size == 0? 99999 : ask_price) << '\n';
}
void print_quote(priority_queue<sell_order> &sos, priority_queue<buy_order> &bos, const unordered_set<int> &cancelled)
{
    print_quote(bos, sos, cancelled);
}

template <typename IN, typename WAIT>
void process_incoming(priority_queue<IN> &incoming, priority_queue<WAIT> &waiting, unordered_set<int> &cancelled, int seq)
{
    int size, price;
    cin >> size >> price;
    while (!waiting.empty())
    {
        auto &top_waiting = waiting.top();
        if (cancelled.count(top_waiting.seq))
        {
            waiting.pop();
            continue;
        }
        if (can_trade(price, top_waiting))
        {
            auto top_order = top_waiting;
            waiting.pop();
            int trade_price = top_order.price;
            int trade_size = min(top_order.size, size);
            cout << "TRADE " << trade_size << " " << trade_price << '\n';
            size -= trade_size;
            top_order.size -= trade_size;
            if (top_order.size)
            {
                waiting.push(top_order);
                break;
            }
        }
        else
            break;
    }
    if (size)
        incoming.push({price, size, seq});

    print_quote (incoming, waiting, cancelled);
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
        priority_queue<buy_order> buy_orders;
        priority_queue<sell_order> sell_orders;
        unordered_set<int> cancel;
        for (auto i = 1; i <= n; ++i)
        {
            string cmd; cin >> cmd;
            if (cmd[0] == 'B')
                process_incoming(buy_orders, sell_orders, cancel, i);
            else if (cmd[0] == 'S')
                process_incoming(sell_orders, buy_orders, cancel, i);
            else // cancel order
            {
                int ci; cin >> ci;
                cancel.insert(ci);
                print_quote(buy_orders, sell_orders, cancel);
            }
        }
    }

    return 0;
}


