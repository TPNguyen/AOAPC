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

struct Game {
    deque<int> blocks[4];
    friend istream& operator>>(istream& is, Game &g)
    {
        for (auto i = 0; i < 4; ++i)
            g.blocks[i].clear();

        int num[24];
        for (int i = 0; i < 24 && is; ++i)
            is >> num[i];
        if (is)
        {
            g.blocks[0].push_back(num[0]);
            g.blocks[1].push_back(num[1]);
            g.blocks[0].push_back(num[2]);
            g.blocks[1].push_back(num[3]);

            for (int i = 4; i < 11; ++i)
                g.blocks[2].push_front(num[i]);

            g.blocks[0].push_back(num[6]);
            g.blocks[1].push_back(num[8]);
            g.blocks[0].push_back(num[11]);
            g.blocks[1].push_back(num[12]);

            for (int i = 13; i < 20; ++i)
                g.blocks[3].push_front(num[i]);

            g.blocks[0].push_back(num[15]);
            g.blocks[1].push_back(num[17]);
            g.blocks[0].push_back(num[20]);
            g.blocks[1].push_back(num[21]);
            g.blocks[0].push_back(num[22]);
            g.blocks[1].push_back(num[23]);
        }

        return is;
    }

    bool same(int num)
    {
        for (auto i = 0; i < 4; ++i)
        {
            for (auto j = 2; j < 5; ++j)
                if (blocks[i][j] != num) return false;
        }
        return true;
    }

    vector<int> init_count()
    {
        vector<int> ret{1,2,3};
        vector<int> count(3);
        for (auto i = 2; i < 5; ++i)
        {
            count[blocks[2][i]-1]++;
            count[blocks[3][i]-1]++;
        }

        count[blocks[0][3]-1]++;
        count[blocks[1][3]-1]++;

        sort(ret.begin(), ret.end(), [&count](int a, int b){ return count[a-1] > count[b-1];});
        return ret;
    }

    void rotate(int which)
    {
        bool bakward = which > 3;
        if (bakward)
        {
            if (which < 6)
                which = 5-which;
            else
                which = 9-which;
        }

        if (bakward)
        {
            auto remove = blocks[which].back();
            blocks[which].pop_back();
            blocks[which].push_front(remove);
        }
        else
        {
            auto remove = blocks[which].front();
            blocks[which].pop_front();
            blocks[which].push_back(remove);
            // blocks[which].splice(blocks[which].end(), blocks[which], blocks[which].begin());
        }

        int third = blocks[which][2];
        int bthird = blocks[which][4];
        switch (which)
        {
            case 0:
                blocks[2][4] = third;
                blocks[3][4] = bthird;
                break;
            case 1:
                blocks[2][2] = third;
                blocks[3][2] = bthird;
                break;
            case 2:
                blocks[0][2] = bthird;
                blocks[1][2] = third;
                break;
            case 3:
                blocks[0][4] = bthird;
                blocks[1][4] = third;
                break;
        }
    }
    int Hash(int which)
    {
        int ret = 0;
        int setbit = 1;
        for (auto i = 0; i < 4; ++i)
        {
            for (auto d: blocks[i])
            {
                if (d == which)
                    ret |= setbit;
                setbit <<= 1;
            }
        }
        return ret;
    }
};

int main()
{
    Game g;
    while (cin >> g)
    {
        vector<char> finalpath;
        int minlen = numeric_limits<int>::max();
        int cnter;
        auto sequ = g.init_count();
        for (auto tgt: sequ)
        {
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

