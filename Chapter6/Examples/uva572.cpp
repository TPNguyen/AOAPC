#include <iostream>
#include <cstring>

char grid[102][102];
bool visited[102][102];
int di[8] = {-1, -1, -1,  0, 0,  1, 1, 1}; 
int dj[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
int m, n, result;

void dfs(int I, int J);
int main()
{
    while(std::cin >> m >> n)
    {
        if(m == 0) return 0;

        result = 0;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                std::cin >> grid[i][j]; // cin should ignore white space.

        memset(visited, 0, sizeof(visited));

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if(!visited[i][j] && grid[i][j] == '@')
                {
                    result++;
                    dfs(i, j);
                } 
        std::cout << result << "\n";
    }; 

    return 0;
} 

void dfs(int I, int J)
{
    visited[I][J] = 1;
    for(int i = 0; i < 8; ++i)
    {
        int newI = I+di[i], newJ = J+dj[i];
        if(newI < m && newI >= 0 && newJ >= 0 && newJ < n && !visited[newI][newJ] && grid[newI][newJ]=='@')  // within range
            dfs(newI, newJ);

    }
}
