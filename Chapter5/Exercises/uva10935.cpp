// Throwing cards away I, UVa 10935

#include <deque>
#include <iostream>
using namespace std;

void simulate(deque<int> &deck);
int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    while (cin >> n && n)
    {
        deque<int> cards(n+1);
        for (auto i = 1; i <= n; ++i)
            cards[i] = i;

        simulate(cards);
    }

    return 0;
}

void simulate(deque<int> &deck)
{
    cout << "Discarded cards:";
    deck.pop_front();
    if (deck.size() > 1)
    {
        deck.pop_front();
        deck.push_back(deck.front());
        deck.pop_front();
        cout << " 1";
    }

    while (deck.size() > 1)
    {
        auto discard = deck.front();
        deck.pop_front();
        deck.push_back(deck.front());
        deck.pop_front();

        cout << ", " << discard;
    }

    cout << "\nRemaining card: " << deck.front() << "\n";
}
