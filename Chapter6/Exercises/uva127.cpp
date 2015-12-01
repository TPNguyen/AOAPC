#include <iostream>
#include <stack>
#include <list>
#include <utility>

typedef std::pair<char, char> card;
typedef std::stack<card> pile;
typedef std::list<pile> accordian;

inline bool match(const card& a, const card& b)
{
    return (a.first == b.first || a.second == b.second);
}

bool move(accordian* game, accordian::iterator left, accordian::iterator right);
void domove(accordian* game);

inline void print_piles(accordian* game)
{
    accordian::iterator it = game->begin();
    for( ; it != game->end(); ++it)
        std::cout << it->top().first << it->top().second << " ";
    std::cout << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    while(1)
    {
        accordian game;
        // read in 52 cards
        for(int i = 0; i < 52; i++)
        {
            std::string s;
            std::cin >> s;
            if(s == "#")
                return 0;

            // construct a card
            card next_card = std::make_pair(s[0], s[1]);
            // construct a pile of card, initially contains only 1 card
            pile next_pile;
            next_pile.push(next_card);
            // put the pile at the back
            game.push_back(next_pile);
        }
        //print_piles(&game);
        domove(&game);
        //print_piles(&game);

    }
}

void domove(accordian* game)
{
MOVE:
    // Handle the case of 1 2 3 which neither card has an 3rd card to the left
    accordian::iterator prev = game->begin();
    accordian::iterator curr = ++game->begin();
    for(int i = 0; i < game->size() - 1 && i < 2; i++)
    {
        if(move(game, prev, curr)) goto MOVE;
        ++prev, ++curr;
    }

    for( ; curr != game->end(); ++curr)
    {
        prev = curr;
        std::advance(prev, -3);
        if(move(game, prev, curr)) goto MOVE;

        prev = curr;
        std::advance(prev, -1);
        if(move(game, prev, curr)) goto MOVE;
    }

    // Print the pile info
    std::string plural = game->size() > 1? "piles" : "pile";
    std::cout << game->size() << " " << plural << " remaining:";
    curr = game->begin();
    for( ; curr != game->end(); ++curr)
        std::cout << " " << curr->size();
    std::cout << std::endl;
}

bool move(accordian* game, accordian::iterator left, accordian::iterator right)
{ 
    if(match(left->top(), right->top()))
    {
        left->push(right->top());
        right->pop();
        // If no card left on the pile
        if(right->empty())
            game->erase(right);

        return true;
    }
    return false;
}
