#include <iostream>
#include <vector>
#include <string>

int main()
{
    int numtor, denom;
    while (std::cin >> numtor >> denom)
    {
        std::cout << numtor << "/" << denom << " = ";

        std::string result; // stores the quotient
        std::vector<int> remainders(denom, -1); // remainder is index, value is index into the quotient

        auto quot = numtor / denom, rem = numtor % denom;
        auto deci = 0;

        auto quot_b4_point = quot;

        for (; remainders[rem] == -1; ++deci)
        {
            remainders[rem] = deci;
            numtor = rem * 10;
            quot = numtor / denom; rem = numtor % denom;
            result += std::to_string(quot);
        }
        auto first_occur = remainders[rem];
        auto cycle_len = deci - first_occur;

        auto fresult = std::to_string(quot_b4_point) + '.' + result.substr(0, first_occur) ;
        if (deci > 50)
            fresult += '(' + result.substr(first_occur, 50-first_occur) + "...)";
        else
            fresult += '(' + result.substr(first_occur, cycle_len) + ')';

        std::cout << fresult << "\n";
        std::cout << "   " << cycle_len << " = number of digits in repeating cycle\n\n";
    }

    return 0;
}

