#include <string>
#include <iostream>
#include <cctype>

const char* rev = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const char* msg[] = {"not a palindrome", "a regular palindrome", "a mirrored string", "a mirrored palindrome"};

const char tr(const char& c)
{
    if (std::isalpha(c))
        return rev[c-'A'];
    if (std::isdigit(c))
        return rev[c-'0'+25];
}
int main()
{
    std::string s;
    while(std::cin >> s)
    {
        auto len = s.size();
        int p = 1, m = 1;

        for (std::string::size_type i = 0; i < (len+1)/2; ++i)
        {
            if (s[i] != s[len-1-i]) p = 0;
            if (tr(s[i]) != s[len-1-i]) m = 0;
        }

        std::cout << s << " -- is " << msg[m*2+p] << ".\n\n";
    }

    return 0;
}
