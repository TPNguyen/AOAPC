// The Rotation Game, Shanghai 2004, UVa 1343
// TLE!!!

#include <deque>
#include <queue>
#include <iostream>
#include <iterator>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <limits>
#include <algorithm>
using namespace std;

int line[8][7] = {
    { 0,  2,  6, 11, 15, 20, 22},
    { 1,  3,  8, 12, 17, 21, 23},
    {10,  9,  8,  7,  6,  5,  4},
    {19, 18, 17, 16, 15, 14, 13},
};

const int rev[8] = {5, 4, 7, 6, 1, 0, 3, 2};
const int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};

struct Game {
    int blocks[24];
    friend istream& operator>>(istream& is, Game &g)
    {
        for (int i = 0; i < 24 && is; ++i)
            is >> g.blocks[i];

        return is;
    }

    bool same(int num)
    {
        for (auto i = 0; i < 8; ++i)
        {
            if (blocks[center[i]] != num) return false;
        }
        return true;
    }

    vector<int> init_count()
    {
        vector<int> ret{1,2,3};
        vector<int> count(3);
        for (auto i = 0; i < 8; ++i)
        {
            count[blocks[center[i]]-1]++;
        }

        sort(ret.begin(), ret.end(), [&count](int a, int b){ return count[a-1] > count[b-1];});
        return ret;
    }

    void rotate(int which)
    {
        int temp = blocks[line[which][0]];
        for (int j = 0; j < 6; ++j)
            blocks[line[which][j]] = blocks[line[which][j+1]];
        blocks[line[which][6]] = temp;
    }

    int Hash(int which)
    {
        int ret = 0;
        int setbit = 1;
        for (auto i = 0; i < 24; ++i)
        {
            if (blocks[i] == which)
                ret |= setbit;
            setbit <<= 1;
        }
        return ret;
    }
};

int main()
{
    for (auto i = 4; i < 8; ++i)
        for (auto j = 0; j < 7; ++j)
        line[i][j] = line[rev[i]][6-j];
    Game g;
    while (cin >> g)
    {
        vector<char> finalpath;
        int minlen = numeric_limits<int>::max();
        int cnter;
        auto sequ = g.init_count();
        for (auto tgt: sequ)
        {
            // cout << "working on " << tgt <<  "\n";
            if (minlen == 0) break;
            queue<Game> Q;
            queue<int> dist;
            vector<int> fa; unordered_set<int> vis; vector<char> last_move_direc;

            Q.push(g);
            fa.push_back(-1);
            vis.insert(g.Hash(tgt));
            dist.push(0);
            last_move_direc.push_back('\0');

            bool found = false;
            int front = 0, rear = 1;
            while (front < rear)
            {
                Game g = Q.front(); Q.pop();
                int cur_dist = dist.front(); dist.pop();
                if (cur_dist > minlen)
                {
                    found = false;
                    break;
                }
                if (g.same(tgt))
                {
                    found = true;
                    break;
                }

                for (auto i = 0; i < 8; ++i)
                {
                    Game nextg = g;
                    nextg.rotate(i);
                    bool inserted = false;
                    std::tie(std::ignore, inserted) = vis.insert(nextg.Hash(tgt));
                    if (inserted)
                    {
                        Q.push(nextg);
                        fa.push_back(front);
                        dist.push(cur_dist+1);
                        last_move_direc.push_back('A'+i);
                        rear++;
                    }
                }

                front++;
            }
            if (found)
            {
                // reconstrct path
                vector<char> paths;
                while (fa[front] != -1)
                {
                    paths.push_back(last_move_direc[front]);
                    front = fa[front];
                }

                int totalsteps = paths.size();
                if (totalsteps < minlen || (totalsteps == minlen && paths[totalsteps-1] < finalpath[totalsteps-1]))
                {
                    cnter = tgt;
                    finalpath = paths;
                    minlen = totalsteps;
                }
            }
        }
        if (minlen == 0)
            cout << "No moves needed";
        for (auto i = minlen-1; i >= 0; --i)
            cout << finalpath[i];
        cout << "\n" << cnter << "\n";
    }

    return 0;
}


