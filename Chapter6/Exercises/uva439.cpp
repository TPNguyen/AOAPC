// As in DFS, BFS also needs marking!
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <utility>
#include <cstring>

typedef std::pair<int, int> coord;

int di[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dj[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
bool visited[8][8];
//functions
int bfs(std::queue<std::pair<coord, int> >& Q, coord end);
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::string start, end;
    while(std::cin >> start >> end)
    {
        int  start_col = start[0]-'a', start_row = start[1]-'1',
             end_col = end[0]-'a', end_row = end[1]-'1';

        std::queue<std::pair<coord, int> > Q;
        memset(visited, 0, sizeof(visited));
        visited[start_row][start_col] = true;
        Q.push(std::make_pair(std::make_pair(start_row, start_col), 0));
        coord endCoord = std::make_pair(end_row, end_col);
        std::cout << "To get from " << start << " to " << end << " takes " << bfs(Q, endCoord) << " knight moves.\n";
    }

    return 0;
}

int bfs(std::queue<std::pair<coord, int> >& Q, coord end)
{
    while(!Q.empty())
    {
        coord front = Q.front().first;
        int level = Q.front().second;

        if(front == end) return level;

        Q.pop();
        int newI, newJ;
        level++;
        for(int k = 0; k < 8; ++k)
        {
            newI = front.first + di[k], newJ = front.second + dj[k];
            if(newI >= 0 && newI < 8 && newJ >= 0 && newJ < 8 && !visited[newI][newJ])
            {
                visited[newI][newJ] = true;
                Q.push(std::make_pair(std::make_pair(newI, newJ), level));
            }
        }
    }

    return -1;
}
