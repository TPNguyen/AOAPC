// Urban Elevations; UVa 221

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int MAXN = 103;
struct Building
{
    double x, y, width, depth, height;
} city_map[MAXN];

int num_build;

// read in city map
inline bool init()
{
    cin >> num_build;
    for (auto i = 1; i <= num_build; ++i)
    {
        auto &b = city_map[i];
        cin >> b.x >> b.y >> b.width >> b.depth >> b.height;
    }

    return num_build > 0;
}

bool is_visible(int build_i)
{
    using interv = pair<double, double>;

    auto &target = city_map[build_i];

    vector<interv> visible_inverv;
    visible_inverv.push_back({target.x, target.x+target.width});

    for (auto i = 1; i <= num_build && visible_inverv.size(); ++i)
    {
        if (i == build_i)   continue;
        auto &bi = city_map[i];
        auto bix = bi.x;
        auto biX = bi.x + bi.width;
        // if current building is shorter OR not in front OR no overlap at all
        if (bi.height < target.height || bi.y+bi.depth > target.y
                || biX <= visible_inverv.front().first || bix >= visible_inverv.back().second)  continue;

        vector<interv> after_block;
        for (auto &visi: visible_inverv)
        {
            // block none
            if (biX <= visi.first || bix >= visi.second)
                after_block.push_back(std::move(visi));
            // block all visi
            else if (bix <= visi.first && biX >= visi.second)
                ;
            // block left part
            else if (bix <= visi.first)
                after_block.push_back({biX, visi.second});
            // block right part
            else if (biX >= visi.second)
                after_block.push_back({visi.first, bix});
            // block middle
            else
            {
                after_block.push_back({visi.first, bix});
                after_block.push_back({biX, visi.second});
            }
        }

        // update visible_inverv
        visible_inverv = std::move(after_block);
    }

    return visible_inverv.size();
}

inline void display(const vector<int> &seq)
{
    cout << seq[0];
    for (auto i = 1; i < seq.size(); ++i)
    {
        cout << " " << seq[i];
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);

    int kase = 0;
    while(init())
    {
        vector<int> visible_seqs;
        for (auto i = 1; i <= num_build; ++i)
            if (is_visible(i))
                visible_seqs.push_back(i);

        sort(visible_seqs.begin(), visible_seqs.end(), [](int a, int b) { 
                if (city_map[a].x < city_map[b].x) return true;
                else if (city_map[a].x == city_map[b].x && city_map[a].y < city_map[b].y) return true;
                else return false;
                });

        if (kase) cout << "\n";
        cout << "For map #" << ++kase << ", the visible buildings are numbered as follows:\n";
        display(visible_seqs);
    }

    return 0;
}
