// Database, UVa 1592

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <utility>
using namespace std;

constexpr int MAXROW = 10010, MAXCOL = 12;

inline void insert_cols(unordered_map<string, int> &db, string &c, int &seq, int &table)
{
    auto iresult = db.insert({c, seq});
    if (iresult.second == false)
        table = iresult.first->second;
    else
        table = seq++;
}

int main()
{
    ios_base::sync_with_stdio(false);

    int table[MAXROW][MAXCOL];
    int numrow, numcol;
    while (cin >> numrow >> numcol && cin.ignore(100, '\n'))
    {
        unordered_map<string, int> database_cols;
        // map<string, int> database_cols;
        int seq = 0;
        for (auto i = 0; i < numrow; ++i)
        {
            string content;
            for (auto j = 0; j < numcol-1; ++j)
            {
                getline(cin, content, ',');
                insert_cols(database_cols, content, seq, table[i][j]);
            }
            getline(cin, content);
            insert_cols(database_cols, content, seq, table[i][numcol-1]);
                /*if (!database_cols.count(content))
                {
                    database_cols[content] = ++seq;
                    table[i][j] = seq;
                }
                else
                    table[i][j] = database_cols[content];
                    */
                    
                /* Map is slow (AC 1.498)
                    */
        }

        bool found = false;
        for (auto c1 = 0; c1 < numcol-1 && !found; ++c1)
        {
            for (auto c2 = c1+1; c2 < numcol && !found; ++c2)
            {
                // unordered_map<pair<int, int>, int> cols2row;
                unordered_map<long long, int> cols2row;
                for (auto r = 0; r < numrow && !found; ++r)
                {
                    long long cols = (static_cast<long long>(table[r][c1]) << 32) | table[r][c2];
                    // pair<int, int> cols {table[r][c1], table[r][c2]};
                    // version 1 (ac 0.822)
                    /*auto updateoradd = cols2row.lower_bound(cols);
                    if (updateoradd != cols2row.end() && !(cols2row.key_comp()(cols, updateoradd->first)))
                    {
                        cout << "NO\n";
                        cout << cols2row[cols]+1 << ' ' << r+1 << '\n';
                        cout << c1+1 << ' ' << c2+1 << '\n';
                        found = true;
                    }
                    else
                        cols2row.insert(updateoradd, {cols, r});
                        */

                    // version 2 (AC 0.818)
                    auto iresult = cols2row.insert({cols, r});
                    if (iresult.second == false) // cols already exist
                    {
                        cout << "NO\n";
                        cout << iresult.first->second+1 << ' ' << r+1 << '\n';
                        cout << c1+1 << ' ' << c2+1 << '\n';
                        found = true;
                    }
                }
            }
        }

        if (!found)
            cout << "YES\n";

    }

    return 0;
}



