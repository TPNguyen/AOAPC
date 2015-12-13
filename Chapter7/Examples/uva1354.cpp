// Mobile Computing, ACM/ICPC Tokyo 2005, UVa 1354

#include <iostream>
#include <algorithm>
#include <memory>
#include <tuple>
#include <iomanip>
using namespace std;

constexpr int MAXW = 8;
int weights[MAXW];
double r, maxwidth;
struct Node {
    int w = 0; // if zero, it is a mobile
    shared_ptr<Node> left = nullptr;
    shared_ptr<Node> right = nullptr;
    Node() = default;
    Node(int W) : w(W) {}
};

void dfs(const vector<shared_ptr<Node>> &subtrees);
tuple<int, double, double> calc_width(const shared_ptr<Node> &root);
int main()
{
    // ios_base::sync_with_stdio(false);
    int N; cin >> N;
    while (N--)
    {
        cin >> r; maxwidth = -1;
        int s; cin >> s;
        for (auto i = 0; i < s; ++i)
            cin >> weights[i];

        // sort(weights, weights+s);
        vector<shared_ptr<Node>> pnodes;
        for (auto i = 0; i < s; ++i)
            pnodes.push_back(std::make_shared<Node>(weights[i]));

        // do {
            dfs(pnodes);
        // } while (std::next_permutation(weights, weights+s));

        // if (maxwidth < 0)
        //     cout << "-1\n";
        // else
            cout << fixed << setprecision(15) << maxwidth << "\n";
    }

    return 0;
}

void dfs(const vector<shared_ptr<Node>> &subtrees)
{
    auto numtrees = subtrees.size();
    if (numtrees == 1) // base case; mobile is constructed.
    {
        // calc max width and update global one if appropriate
        double ll, rr;
        std::tie(std::ignore, ll, rr) = calc_width(subtrees[0]);
        if (ll + rr < r)
            maxwidth = max(maxwidth, ll+rr);
        return;
    }
    for (auto i = 0; i < numtrees; ++i)
    {
        for (auto j = 0; j < numtrees; ++j)
        {
            if (j == i) continue;
            // create new subtree by joining subtrees[i] and subtrees[j]
            auto joined = std::make_shared<Node>();
            // shared_ptr<Node> joined(new Node);
            joined->left = subtrees[i], joined->right = subtrees[j];
            vector<shared_ptr<Node>> reduced;
            for (auto k = 0; k < numtrees; ++k)
            {
                if (k == i || k == j) continue;
                reduced.push_back(subtrees[k]);
            }
            reduced.push_back(joined);

            dfs(reduced);
        }
    }
}

tuple<int, double, double> calc_width(const shared_ptr<Node> &root)
{
    if (root->w) // this is a weight
    {
        return std::make_tuple(root->w, 0, 0);
    }
    // if (root->w == 0) // this is a mobile

    int lw; double ll, lr;
    int rw; double rl, rr;
    std::tie(lw, ll, lr) = calc_width(root->left);
    std::tie(rw, rl, rr) = calc_width(root->right);
    double additional_left = static_cast<double>(rw)/(lw+rw);
    double additional_right = 1 - additional_left;

    if (rl-1 > ll) ll = rl-1;
    if (lr-1 > rr) rr = lr-1;
    return std::make_tuple(lw+rw, ll+additional_left, rr+additional_right);
}

