#include <iostream>
#include <bitset>
#include <string>

enum class outcome{WIN, LOSE, CHICK};
std::string::size_type guess(std::string &, char);
int main()
{
    int rnd;
    std::string answer, guessed;
    while (std::cin >> rnd >> answer >> guessed && rnd != -1)
    {
        // print header
        std::cout << "Round " << rnd << "\n";

        outcome rel = outcome::CHICK;
        std::bitset<26> occured;
        auto answer_len = answer.size();
        decltype(answer_len) total_num_guessed = 0;
        auto hangman = 0;

        for (const auto c: guessed)
        {
            if (occured.test(c-'a'))
                continue;
            occured.set(c-'a');
            auto num_guessed = guess(answer, c);
            total_num_guessed += num_guessed;

            if (num_guessed == 0)
                ++hangman;

            if (hangman == 7) rel = outcome::LOSE;
            if (total_num_guessed == answer_len) rel = outcome::WIN;

            if (rel != outcome::CHICK)
                break;
        }

        if (rel == outcome::WIN)
            std::cout << "You win.\n";
        else if (rel == outcome::LOSE)
            std::cout << "You lose.\n";
        else
            std::cout << "You chickened out.\n";
    }

    return 0;
}

std::string::size_type guess(std::string &real_answer, char guess_c)
{
    std::string::size_type count = 0;
    for (const auto c: real_answer)
        if (c == guess_c)
            ++count;

    return count;
}



