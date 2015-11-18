// Do you know the way to San Jose?, ACM/ICPC World Finals 1997, UVa511

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>

using namespace std;

using coord = pair<double, double>;
double dist(const coord &A, const coord &B)
{
    return (A.first-B.first)*(A.first-B.first) + (A.second-B.second)*(A.second-B.second);
}
struct Map {
    string name;
    coord x1y1;
    coord x2y2;
    double area;
    double aspectr;
};
struct Loc {
    string name;
    coord xy;
    Loc() = default;
    Loc(const string &n) : name(n), xy() {}
};

vector<Map> mapvec;
vector<Loc> locset;
void do_input()
{
    ios_base::sync_with_stdio(false);
    string line; cin >> line;
    Map m;
    if (line == "MAPS")
    {
        while (true) {
            cin >> m.name;
            if (m.name == "LOCATIONS")
                break;
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (x1 > x2) std::swap(x1, x2);
            if (y1 > y2) std::swap(y1, y2);
            m.x1y1.first = x1; m.x1y1.second = y1;
            m.x2y2.first = x2; m.x2y2.second = y2;
            m.area = (x2-x1) * (y2-y1);
            m.aspectr = (y2-y1)/(x2-x1);
            mapvec.push_back(m);
        }
    }
    if (m.name == "LOCATIONS")
    {
        Loc loc;
        while (true)
        {
            cin >> loc.name;
            if (loc.name == "REQUESTS")
                break;
            cin >> loc.xy.first >> loc.xy.second;
            locset.push_back(loc);
        }
    }
}

int main()
{
    do_input();
    auto loc_cmp = [](const Loc &l1, const Loc &l2){return l1.name < l2.name;};
    sort(locset.begin(), locset.end(), loc_cmp);
    string city;
    while (cin >> city && city != "END")
    {
        int detail; cin >> detail;
        auto loc_it = equal_range(locset.begin(), locset.end(), Loc(city), loc_cmp);
        if (loc_it.first != loc_it.second)
        {
            auto &loc_xy = loc_it.first->xy;
            auto map_contain = [&loc_xy](const Map &m) -> bool
            {
                double x = loc_xy.first, y = loc_xy.second;
                return x >= m.x1y1.first && x <= m.x2y2.first && y >= m.x1y1.second && y <= m.x2y2.second;
            };
            vector<Map> eligibles;
            copy_if(mapvec.begin(), mapvec.end(), back_inserter(eligibles), map_contain);

            if (eligibles.size())
            {
                /*auto map_cmp = [&loc_xy](const Map &m1, const Map &m2) -> bool
                {
                    if (m1.area != m2.area) return m1.area > m2.area;
                    coord center1 {(m1.x1y1.first+m1.x2y2.first)/2, (m1.x1y1.second+m1.x2y2.second)/2};
                    coord center2 {(m2.x1y1.first+m2.x2y2.first)/2, (m2.x1y1.second+m2.x2y2.second)/2};
                    double dist1 = dist(loc_xy, center1), dist2 = dist(loc_xy, center2);
                    if (dist1 != dist2) return dist1 > dist2;
                    if (m1.aspectr != m2.aspectr) return abs(m1.aspectr-0.75) > abs(m2.aspectr-0.75);
                    dist1 = dist(loc_xy, {m1.x2y2.first, m1.x1y1.second});
                    dist2 = dist(loc_xy, {m2.x2y2.first, m2.x1y1.second});
                    if (dist1 != dist2) return dist1 < dist2;
                    return m1.x1y1.first > m2.x1y1.first;
                };*/
                auto map_cmp = [](const Map &m1, const Map &m2) { return m1.area > m2.area; };
                stable_sort(eligibles.begin(), eligibles.end(), map_cmp);
                auto uniq_end = unique(eligibles.begin(), eligibles.end(), [](const Map &m1, const Map &m2){return m1.area == m2.area; } );

                cout << city << " at detail level " << detail;
                if (detail > distance(eligibles.begin(), uniq_end))
                    // cout << " no map at that detail level; using " << eligibles.back().name << "\n";
                    cout << " no map at that detail level; using " << (--uniq_end)->name << "\n";
                else
                    cout << " using " << eligibles[detail-1].name << "\n";
            }
            else
            {
                cout << city << " at detail level " << detail << " no map contains that location\n";
            }
        }
        else
        {
            cout << city << " at detail level " << detail << " unknown location\n";
        }
    }

    return 0;
}


