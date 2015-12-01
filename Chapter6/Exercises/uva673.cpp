// Parentheses Balance, UVa 673
#include <iostream>
#include <string>
#include <stack>

bool correct(const std::string& word);

int main()
{
    std::ios_base::sync_with_stdio(false);
    int num_strings = 0;
    std::cin >> num_strings;

    std::string word;
    std::getline(std::cin, word);
    while (num_strings--)
    {
        std::getline(std::cin, word);
        if(correct(word))
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }

    return 0;
}

bool correct(const std::string& word)
{
    if(word.empty())
        return true;
    std::stack<char> S;
    for(const auto &w: word)
    {
        if (w == ' ') continue;
        if (w == '(' || w == '[')
            S.push(w);
        else
        {
            if (S.empty())
                return false;
            if (w == ')' && S.top() == '(')
                S.pop();
            else if (w == ']' && S.top() == '[')
                S.pop();
            else
                return false;
        }
    }

    return S.empty();
}
