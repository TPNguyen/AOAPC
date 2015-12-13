// The Rotation Game, Shanghai 2004, UVa 1343
// TLE!!!

#include <list>
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
    list<int> blocks[4];
    friend bool operator== (const Game &g1, const Game &g2)
    {
        for (auto i = 0; i < 4; ++i)
            if (g1.blocks[i] != g2.blocks[i])
                return false;
        return true;
    }
    friend bool operator!= (const Game &g1, const Game &g2)
    {
        return !(g1==g2);
    }
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
            auto it = blocks[i].begin();
            std::advance(it, 2);
            for (auto j = 0; j < 3; ++j, ++it)
                if (*it != num) return false;
        }
        return true;
    }

    vector<int> init_count()
    {
        vector<int> ret{1,2,3};
        vector<int> count(3);
        auto it = blocks[2].begin();
        std::advance(it, 2);
        for (auto j = 0; j < 3; ++j, ++it)
            count[*it-1]++;
        it = blocks[3].begin();
        std::advance(it, 2);
        for (auto j = 0; j < 3; ++j, ++it)
            count[*it-1]++;

        it = blocks[0].begin();
        std::advance(it, 3);
        count[*it-1]++;
        it = blocks[1].begin();
        count[*it-1]++;

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
            blocks[which].splice(blocks[which].begin(), blocks[which], --blocks[which].end());
        }
        else
        {
            blocks[which].splice(blocks[which].end(), blocks[which], blocks[which].begin());
        }

        auto sit = blocks[which].begin();
        advance(sit, 2); int third = *sit;
        advance(sit, 2); int bthird = *sit;
        list<int>::iterator tit;
        switch (which)
        {
            case 0:
                tit = blocks[2].end(); advance(tit, -3); *tit = third;
                tit = blocks[3].end(); advance(tit, -3); *tit = bthird;
                break;
            case 1:
                tit = blocks[2].begin(); advance(tit, 2); *tit = third;
                tit = blocks[3].begin(); advance(tit, 2); *tit = bthird;
                break;
            case 2:
                tit = blocks[0].begin(); advance(tit, 2); *tit = bthird;
                tit = blocks[1].begin(); advance(tit, 2); *tit = third;
                break;
            case 3:
                tit = blocks[0].end(); advance(tit, -3); *tit = bthird;
                tit = blocks[1].end(); advance(tit, -3); *tit = third;
                break;
        }
    }
    /*string Hash(int which)
    {
        string ret;
        for (auto i = 0; i < 4; ++i)
        {
            for (auto d: blocks[i])
            {
                if (d != which) d = 0;
                ret += to_string(d);
            }
        }
        return ret;
    }*/
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
