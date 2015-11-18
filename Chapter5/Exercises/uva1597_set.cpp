// Searching the Web, ACM/ICPC Beijing 2004, UVa1597

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <iterator>
#include <utility>
#include <cstring>
using namespace std;

const string tenstar = "**********";
constexpr int MAXN = 102;
using bucket_entry = pair<int, int>; // {doc_num, line_num};

int N;
unordered_map<string, vector<bucket_entry>> inv_index;
vector<string> docu[MAXN];

bool is_binary(const string &line, string &t1, string &t2, const char *op);
bool is_NOT(const string &line, string &t);
void do_AND(const string &t1, const string &t2);
void do_OR(const string &t1, const string &t2);
void do_NOT(const string &t);
void do_normal(const string &t);

int main()
{
    ios_base::sync_with_stdio(false);
    string line;
    getline(cin, line); N = stoi(line);
    for (auto i = 0; i < N; ++i)
    {
        int linenum = 0;
        while (getline(cin, line) && line != tenstar)
        {
            line += '\n';
            docu[i].push_back(line);

            const auto is_alpha = [](const char &c) { return isalpha(c);};
            const auto not_alpha = [](const char &c) { return !isalpha(c);};

            auto line_end = line.end();
            auto itB = find_if(line.begin(), line_end, is_alpha);
            while (itB != line_end)
            {
                auto itE = find_if(itB, line_end, not_alpha);
                string w = string(itB, itE);
                for (auto &c: w)
                    c = tolower(c);
                auto an_entry = make_pair(i, linenum);
                auto ins_pair = inv_index.insert({std::move(w), vector<bucket_entry>{an_entry}});
                if (ins_pair.second == false)
                {
                    if (ins_pair.first->second.back() != an_entry)
                        ins_pair.first->second.push_back(an_entry);
                }

                // update
                itB = find_if(itE, line_end, is_alpha);
            }
            ++linenum;
        }
    }
    // print_inv_index();

    int M;
    getline(cin, line); M = stoi(line);
    for (auto i = 0; i < M; ++i)
    {
        getline(cin, line);
        string term1, term2;
        if (is_binary(line, term1, term2, " AND "))
        {
            do_AND(term1, term2);
        }
        else if (is_binary(line, term1, term2, " OR "))
        {
            do_OR(term1, term2);
        }
        else if (is_NOT(line, term1))
        {
            do_NOT(term1);
        }
        else
        {
            do_normal(line);
        }
    }

    return 0;
}

void do_normal(const string &t)
{
    auto t_bucket = inv_index.find(t);
    if (t_bucket != inv_index.end())
    {
        auto res = t_bucket->second;
        auto prev_doc = res.front().first;
        for (const auto &b: res)
        {
            if (b.first != prev_doc)
            {
                cout << "----------\n";
                prev_doc = b.first;
            }
            cout << docu[b.first][b.second];
        }
    }
    else
        cout << "Sorry, I found nothing.\n";
    cout << "==========\n";
}

void do_AND(const string &t1, const string &t2)
{
    vector<set<bucket_entry>> res;
    auto t1_bucket = inv_index.find(t1);
    if (t1_bucket != inv_index.end())
    {
        auto t2_bucket = inv_index.find(t2);
        if (t2_bucket != inv_index.end())
        {
            auto t1_entries = t1_bucket->second;
            auto t2_entries = t2_bucket->second;
            auto t1_doc_it = t1_entries.begin();
            auto t1_doc_end = t1_entries.end();
            auto t2_doc_it = t2_entries.begin();
            auto t2_doc_end = t2_entries.end();

            const auto cmd_lambda = [](const bucket_entry &b1, const bucket_entry &b2) { return b1.first < b2.first; };

            while (t1_doc_it != t1_doc_end && t2_doc_it != t2_doc_end)
            {
                auto t1_doc = equal_range(t1_doc_it, t1_doc_end, make_pair(t1_doc_it->first, 0), cmd_lambda);
                auto t2_doc = equal_range(t2_doc_it, t2_doc_end, make_pair(t1_doc_it->first, 0), cmd_lambda);

                // AND success
                if (t2_doc.first != t2_doc.second)
                {
                    set<bucket_entry> doc_nums;
                    copy(t1_doc.first, t1_doc.second, inserter(doc_nums, doc_nums.end()));
                    copy(t2_doc.first, t2_doc.second, inserter(doc_nums, doc_nums.end()));
                    res.push_back(std::move(doc_nums));
                }
                // update iterators
                t1_doc_it = t1_doc.second;
                t2_doc_it = t2_doc.second;
            }
        }
    }
    //print(res);
    if (res.size() == 0)
        cout << "Sorry, I found nothing.\n";
    else
    {
        bool first = true;
        for (const auto& doc: res)
        {
            if (first) first = false;
            else cout << "----------\n";
            for (const auto &line: doc)
                cout << docu[line.first][line.second];
        }
    }

    cout << "==========\n";
}

void do_OR(const string &t1, const string &t2)
{
    set<bucket_entry> res;
    auto t1_bucket = inv_index.find(t1);
    auto t2_bucket = inv_index.find(t2);
    {
        if (t1_bucket != inv_index.end())
            copy(t1_bucket->second.begin(), t1_bucket->second.end(), inserter(res, res.end()));
        if (t2_bucket != inv_index.end())
            copy(t2_bucket->second.begin(), t2_bucket->second.end(), inserter(res, res.end()));
    }
    // print(res);
    if (res.size() == 0)
        cout << "Sorry, I found nothing.\n";
    else
    {
        auto prev_doc = res.begin()->first;
        for (const auto &b: res)
        {
            if (b.first != prev_doc)
            {
                cout << "----------\n";
                prev_doc = b.first;
            }
            cout << docu[b.first][b.second];
        }
    }
    cout << "==========\n";
}

void do_NOT(const string &t)
{
    unordered_set<int> not_in_doc;
    auto t_bucket = inv_index.find(t);
    if (t_bucket != inv_index.end())
    {
        auto t_entries = t_bucket->second;
        auto t_doc_it = t_entries.begin();
        auto t_doc_end = t_entries.end();

        transform(t_doc_it, t_doc_end, inserter(not_in_doc, not_in_doc.end()), [](const bucket_entry &b) { return b.first;});
    }
    // print(res);
    bool first = true;
    for (auto i = 0; i < N; ++i)
    {
        if (not_in_doc.count(i))
            continue;
        else
        {
            if (first) first = false;
            else cout << "----------\n";
            for (const auto &l: docu[i])
                cout << l;
        }
    }
    if (first)
        cout << "Sorry, I found nothing.\n";
    cout << "==========\n";

}

bool is_binary(const string &line, string &t1, string &t2, const char *op)
{
    auto mark = line.find(op);
    if (mark != string::npos)
    {
        t1 = line.substr(0, mark);
        t2 = line.substr(mark+strlen(op));
        return true;
    }
    return false;
}

bool is_NOT(const string &line, string &t)
{
    // NOT at beginning of line
    if (line.find("NOT ") == 0)
    {
        t = line.substr(4);
        return true;
    }

    return false;
}

