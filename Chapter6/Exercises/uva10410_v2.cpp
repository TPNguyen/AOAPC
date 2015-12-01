// Tree Reconstruction, UVa 10410
// http://blog.csdn.net/keshuai19940722/article/details/38778243 (very observative! DFS uses stack while BFS uses queue. Mine algorithm uses BFS's queue. His algorithm is bases on DFS's stack and check to see BFS to indicate if dfs is in the same stack frame.
// http://mycodebattle.github.io/2015/04/UVa-10410/
// http://tak3ncpp.github.io/2015/08/29/uva%2010410/
// http://mypaper.pchome.com.tw/zerojudge/post/1324808111
// http://mail.cfanz.cn/index.php?c=article&a=read&id=181777
// http://www.cnblogs.com/zhangyaoqi/p/4591535.html (very similar to my idea)
// http://www.cnblogs.com/20143605--pcx/p/4859424.html (use BFS as reference, work on DFS sequence, the opposite to mine. same as the first link idea)

#include <iostream>
#include <vector>
using namespace std;

constexpr int MAXN = 1024;
constexpr int INF = 2048;
struct Node {
    int dfs_index;
    vector<int> children;
} nodes[MAXN];

int BFS[MAXN];

int main()
{
    int N;
    while (cin >> N)
    {
        for (auto i = 1; i <= N; ++i)
            cin >> BFS[i];
        for (auto i = 1; i <= N; ++i)
        {
            int n; cin >> n;
            nodes[n].dfs_index = i;
            nodes[n].children.clear();
        }

        auto root = BFS[1];

        vector<int> roots; roots.push_back(root);
        auto child_i = 2;
        while (child_i <= N)
        {
            vector<int> children;
            for (auto ri = 0; ri < roots.size() && child_i <= N; ++ri)
            {
                auto root = roots[ri];
                auto root_dfs_i = nodes[root].dfs_index;
                int between_st = root_dfs_i + 1;
                int between_end = (ri == roots.size()-1 ? N : nodes[roots[ri+1]].dfs_index);
                if (between_st == nodes[BFS[child_i]].dfs_index)
                {
                    auto child1 = BFS[child_i];
                    nodes[root].children.push_back(child1);
                    child_i ++;
                    children.push_back(child1);
                    between_st++;

                    while (child_i <= N) {
                        auto child2 = BFS[child_i];
                        if (child2 < child1) // can't be current root's child
                            break;

                        if (nodes[child2].dfs_index >= between_st && nodes[child2].dfs_index <= between_end)
                        {
                            nodes[root].children.push_back(child2);
                            child_i ++;
                            children.push_back(child2);
                            between_st = nodes[child2].dfs_index+1;
                            child1 = child2;
                        }
                        else
                            break;
                    }
                }
            }
            roots = children;
        }

        for (auto i = 1; i <= N; ++i)
        {
            cout << i << ":";
            for (const auto n: nodes[i].children)
                cout << " " << n;
            cout << "\n";
        }
    }

    return 0;
}

