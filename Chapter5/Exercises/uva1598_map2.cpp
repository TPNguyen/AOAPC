// Exchange, ACM/ICPC NEERC 2006, UVa1598

#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <list>
using namespace std;

struct order {
    int size;
    int seq;
};

priority_queue<int> buy_prices;
priority_queue<int, vector<int>, greater<int>> sell_prices;
unordered_map<int, list<order>> bp2queue;
unordered_map<int, list<order>> sp2queue;
unordered_map<int, pair<list<order>*, list<order>::iterator>> seq2iter;
unordered_set<int> gone;

void print_bid()
{
    int bid_size = 0, bid_price = 0;
    while (!buy_prices.empty() && bid_size == 0)
    {
        auto high_buy = buy_prices.top();
        auto &buyq = bp2queue[high_buy];
        for (const auto &b: buyq)
            bid_size += b.size;
        if (bid_size)
            bid_price = high_buy;
        else
            buy_prices.pop();

    }
    cout << bid_size << " " <<  bid_price;
}

void print_ask()
{
    int ask_size = 0, ask_price = 99999;
    while (!sell_prices.empty() && ask_size == 0)
    {
        auto low_sell = sell_prices.top();
        auto &sellq = sp2queue[low_sell];
        for (const auto &s: sellq)
            ask_size += s.size;
        if (ask_size)
            ask_price = low_sell;
        else
            sell_prices.pop();
    }

    cout << ask_size << " " << ask_price;
}

void print_quote()
{
    cout << "QUOTE ";
    print_bid(); cout << " - ";
    print_ask(); cout << endl;
}


bool process_buy(int size, int price, int seq, list<order> **bl, list<order>::iterator &bit)
{
    // int size, price;
    // cin >> size >> price;
    while (!sell_prices.empty() && size)
    {
        auto lowest_sell = sell_prices.top();
        if (price >= lowest_sell)
        {
            auto &sellq = sp2queue[lowest_sell];
            while (!sellq.empty() && size)
            {
                int &sell_size = sellq.front().size;
                int trade_size = min(sell_size, size);
                cout << "TRADE " << trade_size << " " << lowest_sell << '\n';
                size -= trade_size;
                sell_size -= trade_size;
                if (!sell_size)
                {
                    gone.insert(sellq.front().seq);
                    sellq.pop_front();
                }
            }
            if (sellq.empty())
                sell_prices.pop();
        }
        else break;
    }
    auto ret = false;
    if (size)
    {
        auto &p2q = bp2queue[price];
        if (p2q.empty())
            buy_prices.push(price);
        p2q.push_back({size, seq});
        *bl = &p2q;
        bit = --p2q.end();
        ret = true;
    }
    else
        gone.insert(seq);
    return ret;
}
bool process_sell(int size, int price, int seq, list<order> **sl, list<order>::iterator &sit)
{
    // int size, price;
    // cin >> size >> price;
    while (!buy_prices.empty() && size)
    {
        auto highest_buy = buy_prices.top();
        if (price <= highest_buy)
        {
            auto &buyq = bp2queue[highest_buy];
            while (!buyq.empty() && size)
            {
                int &buy_size = buyq.front().size;
                int trade_size = min(buy_size, size);
                cout << "TRADE " << trade_size << " " << highest_buy << '\n';
                size -= trade_size;
                buy_size -= trade_size;
                if (!buy_size)
                {
                    gone.insert(buyq.front().seq);
                    buyq.pop_front();
                }
            }
            if (buyq.empty())
                buy_prices.pop();
        }
        else break;
    }
    auto ret = false;
    if (size)
    {
        auto &p2q = sp2queue[price];
        if (p2q.empty())
            sell_prices.push(price);
        p2q.push_back({size, seq});
        *sl = &p2q;
        sit = --p2q.end();
        ret = true;
    }
    else
        gone.insert(seq);
    return ret;
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
        vector<string> file(n+1);
        for (auto i = 0; i <= n; ++i)
            getline(cin, file[i]);

        for (auto i = 1; i <= n; ++i)
        {
            if (file[i][0] == 'B')
            {
                auto fspace = file[i].find_first_of(' ');
                auto sspace = file[i].find_first_of(' ', fspace+1);
                auto size = stoi(file[i].substr(fspace+1, sspace-fspace-1));
                auto price = stoi(file[i].substr(sspace+1));
                list<order> *lp;
                list<order>::iterator it;
                if (process_buy(size, price, i, &lp, it))
                    seq2iter.insert({i, {lp, it}});
            }
            else if (file[i][0] == 'S')
            {
                auto fspace = file[i].find_first_of(' ');
                auto sspace = file[i].find_first_of(' ', fspace+1);
                auto size = stoi(file[i].substr(fspace+1, sspace-fspace-1));
                auto price = stoi(file[i].substr(sspace+1));
                list<order> *lp;
                list<order>::iterator it;
                if (process_sell(size, price, i, &lp, it))
                    seq2iter.insert({i, {lp, it}});
            }
            else // cancel order
            {
                auto fspace = file[i].find_first_of(' ');
                auto ci = stoi(file[i].substr(fspace+1));
                if (!gone.count(ci))
                {
                    auto &m = seq2iter[ci];
                    m.first->erase(m.second);
                    gone.insert(ci);
                }
            }
            print_quote ();
        }
        bp2queue.clear();
        sp2queue.clear();
        priority_queue<int> empty; buy_prices.swap(empty);
        priority_queue<int, vector<int>, greater<int>> empty_s; sell_prices.swap(empty_s);
        seq2iter.clear();
        gone.clear();
    }

    return 0;
}

