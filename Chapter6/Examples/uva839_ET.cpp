// Early termination
#include <cstdio>

bool balanced(int* W)
{
    // readin w1, d1, w2, d2
    int w1, d1, w2, d2;
    // A better way is to use getline(std::cin, line) and then call strtol repetatively 
    scanf("%d %d %d %d", &w1, &d1, &w2, &d2);

    if(w1 == 0)
        if(!balanced(&w1))
            return false;

    if(w2 == 0)
        if(!balanced(&w2))
            return false;

    *W = w1 + w2;

    return (w1*d1 == w2*d2);
}

int main()
{
    int num_cases;
    scanf("%d", &num_cases);
    bool blank = false;
    char ignore[12];
    while(num_cases--)
    {
        int W;
        if(blank) printf("\n");
        else
            blank = true;
        if(balanced(&W))
            printf("YES\n");
        else
        {
            printf("NO\n");
            gets(ignore);
            do{
                if(NULL==gets(ignore))
                    break;
            }while(ignore[0] != '\0');
            // printf("%s\n", ignore);
        }
    }

    return 0;
}



