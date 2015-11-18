// Alignment of Code, ACM/ICPC NEERC 2010, UVa 1593

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <iterator>
#include <algorithm>
#include <iomanip>
using namespace std;

constexpr size_t MAXWORDS = 200;
constexpr size_t MAXLINES = 1010;
// denotes the length of each word
string::difference_type lenw[MAXWORDS] = {0};
vector<string> words[MAXLINES];
size_t lineI = 0;

void printAns();
int main()
{
    ios_base::sync_with_stdio(false);
    string line;
    while (getline(cin, line))
    {
        size_t wordI = 0;
        auto it_end = line.cend();
        string::const_iterator wB = it_end;
        for (auto it = line.cbegin(); it != it_end; ++it)
        {
            if (wB == it_end)
            {
                if (isgraph(*it))
                    wB = it;
            }
            else if (*it == ' ')
            {
                // cout << lenw[wordI] << ", " << distance(wB, it) << ";";
                lenw[wordI] = max(lenw[wordI], distance(wB, it));
                words[lineI].emplace_back(wB, it);
                // cout << words[lineI].back() << "(" << lenw[wordI] << ")" << "\n";
                ++wordI;
                wB = it_end;
            }
        }
        if (wB != it_end)
        {
            lenw[wordI] = max(lenw[wordI], distance(wB, it_end));
            words[lineI].emplace_back(wB, it_end);
            // cout << words[lineI].back() << "(" << lenw[wordI] << ")" << "\n";
        }

        ++lineI;
    }

    printAns();

    return 0;
}

void printAns()
{
    cout << left;
    for (size_t li = 0; li < lineI; ++li)
    {
        if (words[li].size())
        {
            for (size_t wi = 0; wi < words[li].size()-1; ++wi)
                cout << setw(lenw[wi]) << words[li][wi] << " ";
            cout << words[li].back() << "\n";
        }
        else
            cout << "\n";
    }
}
