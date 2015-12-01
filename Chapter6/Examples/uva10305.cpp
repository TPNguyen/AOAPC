#include <iostream>
#include <vector>
#include <cstring>

const int MAXN = 110;

int G[MAXN][MAXN];
int depended[MAXN];
int vis[MAXN];
int num_task, precedence;

void dfs(int last, std::vector<int>* st);
int main()
{
    std::ios_base::sync_with_stdio(false);
    while(std::cin >> num_task >> precedence)
    {
        if(num_task == 0)   return 0;

        int before, after;
        for(int i = 0; i < precedence; ++i)
        {
            std::cin >> before >> after;
            G[after][before] = 1;
            depended[before] = 1;
        }

        std::vector<int> st;
        for(int i = 1; i <= num_task; ++i)
        {
            if(!depended[i])
                dfs(i, &st);
        }

        std::cout << st[0];
        for(int i = 1; i < st.size(); ++i)
            std::cout <<" " << st[i];
        std::cout << "\n";
        memset(G, 0, sizeof(G));
        memset(depended, 0, sizeof(depended));
        memset(vis, 0, sizeof(vis));
    }

    return 0;
}

void dfs(int last, std::vector<int>* st)
{
    vis[last] = 1;
    for(int i = 1; i <= num_task; ++i)
    {
        if(G[last][i] && !vis[i])
            dfs(i, st);
    } 
    st->push_back(last);
}
