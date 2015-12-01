// System Dependencies, ACM/ICPC World Finals 1997, UVa 506

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
using namespace std;

struct Item
{
    string name;
    int status = 0; // 0: not installed (or Removed); 1: implicitly installed; 2: explicitly installed
    size_t last_install_at = 0;
    vector<size_t> dependee; // current item depends on dependees
    vector<size_t> depender; // current item is depended by dependers
};
vector<Item> items;
using Index = vector<Item>::size_type;
set<pair<Index, Index>> installed; // {installed_time, index}
Index itime;
using Map = map<string, Index>;
Map item2index;

// prototypes
void Install(Index ind);
bool is_needed(Index id);
void Remove(Index ind);
Index Add(const string &item);

int main()
{
    ios_base::sync_with_stdio(false);
    string cmd;
    while (getline(cin, cmd))
    {
        cout << cmd << "\n";
        string cmd_name, item;
        istringstream iss(cmd); iss >> cmd_name;
        if (cmd_name == "END")
        {
            /*items.clear(); item2index.clear();
            installed.clear();
            itime = 0;*/
            break;
        }
        iss >> item;
        if (cmd_name == "DEPEND")
        {
            auto depender = Add(item);
            while (iss >> item)
            {
                auto dependee = Add(item);
                items[depender].dependee.push_back(dependee);
                items[dependee].depender.push_back(depender);
            }
        }
        else if (cmd_name == "INSTALL")
        {
            auto itemind = Add(item);
            if (items[itemind].status)
                cout << "   " << items[itemind].name << " is already installed.\n";
            else
            {
                Install(itemind);
                items[itemind].status = 2;
            }
        }
        else if (cmd_name == "REMOVE")
        {
            auto itemind = Add(item); // it could remove an item not listed before at all!!!
            if (items[itemind].status == 0)
                cout << "   " << items[itemind].name << " is not installed.\n";
            else if (is_needed(itemind))
                cout << "   " << items[itemind].name << " is still needed.\n";
            else
                Remove(itemind);
        }
        else if (cmd_name == "LIST")
        {
            for (const auto &i: installed)
                cout << "   " << items[i.second].name << "\n";
        }
    }

    return 0;
}

Index Add(const string &item)
{
    Map::iterator it; bool newitem;
    std::tie(it, newitem) = item2index.insert({item, items.size()});
    if (newitem)
    {
        items.push_back(Item());
        items.back().name = item;
    }

    return it->second;
}

void Install(Index ind)
{
    for (const auto &d: items[ind].dependee)
        if (items[d].status == 0)
            Install(d);
    cout << "   Installing " << items[ind].name << "\n";
    items[ind].status = 1;
    items[ind].last_install_at = ++itime;
    installed.insert(installed.end(), {itime,ind});
}

bool is_needed(Index ind)
{
    bool still_needed = false;
    for (const auto &d: items[ind].depender)
        if (items[d].status)
        {
            still_needed = true;
            break;
        }
    return still_needed;
}

void Remove(Index ind)
{
    items[ind].status = 0;
    cout << "   Removing " << items[ind].name << "\n";
    for (const auto &d: items[ind].dependee)
    {
        if (items[d].status != 1 || is_needed(d)) continue;
        Remove(d);
    }
    installed.erase({items[ind].last_install_at, ind});
}
