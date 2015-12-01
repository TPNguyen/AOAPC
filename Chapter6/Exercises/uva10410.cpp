// Tree Reconstruction, UVa 10410

#include <iostream>
#include <vector>
using namespace std;

constexpr int MAXN = 1024;
constexpr int INF = 2048;
struct Node {
    int level = INF;
    int fa;
    int left, right;
    int dfs_index;
} nodes[MAXN];

int BFS[MAXN], DFS[MAXN];

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
            DFS[i] = n;
            nodes[n].dfs_index = i;
        }

        auto root = BFS[1];
        nodes[root].fa = 0;
        nodes[root].level = 0;

        vector<int> roots; roots.push_back(root);
        auto child_i = 2;
        while (child_i <= N)
        {
            vector<int> children;
            for (auto ri = 0; ri < roots.size() && child_i <= N; ++ri)
            {
                auto root = roots[ri];
                auto root_level = nodes[root].level;
                auto root_dfs_i = nodes[root].dfs_index;
                if (root_dfs_i + 1 == nodes[BFS[child_i]].dfs_index)
                {
                    auto child1 = BFS[child_i];
                    nodes[root].left = child1;
                    nodes[child1].fa = root;
                    nodes[child1].level = root_level+1;
                    child_i ++;
                    children.push_back(child1);

                    // The following is wrong. The tree doesn't have to be binary tree. Check v2
                    if (child_i <= N) {
                        auto child2 = BFS[child_i];
                        if (child2 < child1) // can't be current root's child
                            continue;

                        int between_st = root_dfs_i + 2;
                        int between_end = (ri == roots.size()-1 ? N : nodes[roots[ri+1]].dfs_index);
                        if (nodes[child2].dfs_index >= between_st && nodes[child2].dfs_index <= between_end)
                        {
                            nodes[root].right = child2;
                            nodes[child2].fa = root;
                            nodes[child2].level = root_level + 1;
                            child_i ++;
                            children.push_back(child2);
                        }
                    }
                }
            }
            roots = children;
        }

        for (auto i = 1; i <= N; ++i)
        {
            cout << i << ":";
            if (nodes[i].left)
            {
                cout << " " << nodes[i].left;
                if (nodes[i].right) cout << " " << nodes[i].right;
            }
            cout << "\n";
        }
    }

    return 0;
}
