#include <iostream>

bool balanced(int& W)
{
    // readin w1, d1, w2, d2
    int w1, d1, w2, d2;
    bool b1 = true, b2 = true;
    // A better way is to use getline(std::cin, line) and then call strtol repetatively 
    std::cin >> w1 >> d1 >> w2 >> d2;

    if(w1 == 0)
        b1 = balanced(w1);

    if(w2 == 0)
        b2 = balanced(w2);

    W = w1 + w2;

    return b1 && b2 && (w1*d1 == w2*d2);
}

int main()
{
    int num_cases;
    std::cin >> num_cases;
    bool blank = false;
    while(num_cases--)
    {
        int W;
        if(blank) std::cout << "\n";
        else
            blank = true;
        if(balanced(W))
            std::cout << "YES\n";
        else
            std::cout << "NO\n";
    }

    return 0;
}
