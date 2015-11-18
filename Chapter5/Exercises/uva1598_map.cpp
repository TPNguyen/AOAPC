// Exchange, ACM/ICPC NEERC 2006, UVa1598

#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

struct buy_order {
    int size;
    int seq;
};
struct sell_order {
    int size;
    int seq;
};


priority_queue<int> buy_orders;
priority_queue<int, vector<int>, greater<int>> sell_orders;
unordered_map<int, deque<buy_order>> bp2queue;
unordered_map<int, deque<sell_order>> sp2queue;
unordered_set<int> cancelled;

void print_bid()
{
    int bid_size = 0, bid_price = 0;
    while (!buy_orders.empty() && bid_size == 0)
    {
        auto high_buy = buy_orders.top();
        auto &buyq = bp2queue[high_buy];
        for (const auto &b: buyq)
            if (!cancelled.count(b.seq))
                bid_size += b.size;
        if (bid_size)
            bid_price = high_buy;
        else
            buy_orders.pop();

    }
    cout << bid_size << " " <<  bid_price;
}

void print_ask()
{
    int ask_size = 0, ask_price = 99999;
    while (!sell_orders.empty() && ask_size == 0)
    {
        auto low_sell = sell_orders.top();
        auto &sellq = sp2queue[low_sell];
        for (const auto &s: sellq)
            if (!cancelled.count(s.seq))
                ask_size += s.size;
        if (ask_size)
            ask_price = low_sell;
        else
            sell_orders.pop();
    }

    cout << ask_size << " " << ask_price;
}

void print_quote()
{
    cout << "QUOTE ";
    print_bid(); cout << " - ";
    print_ask(); cout << endl;
}


void process_buy(int seq)
{
    int size, price;
    cin >> size >> price;
    while (!sell_orders.empty() && size)
    {
        auto lowest_sell = sell_orders.top();
        if (price >= lowest_sell)
        {
            auto &sellq = sp2queue[lowest_sell];
            while (!sellq.empty() && size)
            {
                if (cancelled.count(sellq.front().seq))
                {
                    sellq.pop_front();
                    continue;
                }
                int &sell_size = sellq.front().size;
                int trade_size = min(sell_size, size);
                cout << "TRADE " << trade_size << " " << lowest_sell << '\n';
                size -= trade_size;
                sell_size -= trade_size;
                if (!sell_size)
                    sellq.pop_front();
            }
            if (sellq.empty())
                sell_orders.pop();
        }
        else break;
    }
    if (size)
    {
        buy_orders.push(price);
        bp2queue[price].push_back({size, seq});
    }
    print_quote ();
}
void process_sell(int seq)
{
    int size, price;
    cin >> size >> price;
    while (!buy_orders.empty() && size)
    {
        auto highest_buy = buy_orders.top();
        if (price <= highest_buy)
        {
            auto &buyq = bp2queue[highest_buy];
            while (!buyq.empty() && size)
            {
                if (cancelled.count(buyq.front().seq))
                {
                    buyq.pop_front();
                    continue;
                }
                int &buy_size = buyq.front().size;
                int trade_size = min(buy_size, size);
                cout << "TRADE " << trade_size << " " << highest_buy << '\n';
                size -= trade_size;
                buy_size -= trade_size;
                if (!buy_size)
                    buyq.pop_front();
            }
            if (buyq.empty())
                buy_orders.pop();
        }
        else break;
    }
    if (size)
    {
        sell_orders.push(price);
        sp2queue[price].push_back({size, seq});
    }
    print_quote ();
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

        for (auto i = 1; i <= n; ++i)
        {
            string cmd; cin >> cmd;
            if (cmd[0] == 'B')
                process_buy(i);
            else if (cmd[0] == 'S')
                process_sell(i);
            else // cancel order
            {
                int ci; cin >> ci;
                cancelled.insert(ci);
                print_quote();
            }
        }
        bp2queue.clear();
        sp2queue.clear();
        priority_queue<int> empty; buy_orders.swap(empty);
        priority_queue<int, vector<int>, greater<int>> empty_s; sell_orders.swap(empty_s);
        cancelled.clear();
    }

    return 0;
}
