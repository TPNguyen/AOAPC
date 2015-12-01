// Khan's algorithm. Depended upon task (has to be finished before) is on the src end of the edge.
// DFS is the opposite. Depended upon task is on the dst end of the edge.
#include <iostream>
#include <queue>
#include <cstring>

const int MAXN = 110;
int G[MAXN][MAXN];
int main()
{
    int num_task, precedence;
    while(std::cin >> num_task >> precedence)
    {
        if(num_task == 0)   return 0;

        int before, after;
        for(int i = 0; i < precedence; ++i)
        {
            std::cin >> before >> after;
            G[before][after] = 1;
            G[after][0]++;
        }

        std::queue<int> Q;
        for(int i = 1; i <= num_task; ++i)
        {
            if(G[i][0]==0)
                Q.push(i);
        }

        bool space = false;
        while(!Q.empty())
        {
            int t = Q.front();
            Q.pop();
            for(int i = 1; i <= num_task; ++i)
            {
                if(G[t][i])
                {
                    G[i][0]--;
                    if(G[i][0]==0)
                        Q.push(i);
                }
            }
            if(space) std::cout << " ";
            else space = true;
            std::cout << t;
        }
        std::cout << "\n";
        memset(G, 0, sizeof(G));
    }

    return 0;
}
