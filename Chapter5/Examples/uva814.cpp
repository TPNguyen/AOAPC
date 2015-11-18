// The letter carrier's rounds, Uva814
// SMTP protocol simulation. 

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>
using namespace std;

namespace {
    using loc_t = string;
    using user_t = string;
    using recplist = vector<vector<string>>;
    using contnt = string;
    map<loc_t, unordered_set<user_t>> MTAs;

    class senderMTA
    {
        public:
            explicit senderMTA(user_t && sn, loc_t && sl, recplist && recp, contnt && m):
                sendername(std::forward<user_t>(sn)), senderloc(std::forward<loc_t>(sl)), recepients(std::forward<recplist>(recp)), msg(std::forward<contnt>(m))
        {}
            senderMTA() = default;
            void send() const;
        private:
            void do_communicate(const vector<string> &l) const;
            // using resp_code = int (senderMTA::*)(int) const;
            int resp_normal(int cmdi) const
            {
                if (cmdi == 0 || cmdi == 1 || cmdi ==4) return 250;
                if (cmdi == 3) return 354;
                if (cmdi == 5) return 221;
            }
            int resp_no_user(const loc_t l, const user_t u) const
            {
                if (MTAs[l].count(u))
                    return 250;
                else
                    return 550;
            }

            // static map<string, resp_code> ftable;
            static vector<string> cmdtable;

            // data members
            user_t sendername;
            loc_t senderloc;
            recplist recepients;
            contnt msg;
    };
    vector<string> senderMTA::cmdtable {"HELO ", "MAIL FROM:", "RCPT TO:", "DATA", "", "QUIT"};

    void senderMTA::send() const
    {
        for (const auto &l: recepients)
            do_communicate(l);
    }
    // This function is ugly. need to factor according to each steps, i.e., create function returning step specific string.
    void senderMTA::do_communicate(const vector<string> &l) const
    {
        string indent = "     ";
        auto it = l.begin();
        auto recp_loc = *it++;
        string output = "Connection between " + senderloc + " and " + recp_loc + "\n";
        // step 0:
        output += indent + cmdtable[0] + senderloc + "\n";
        output += indent + to_string(resp_normal(0)) + "\n";

        // step 1:
        output += indent + cmdtable[1] + "<" + sendername + "@" + senderloc + ">" + "\n";
        output += indent + to_string(resp_normal(1)) + "\n";

        // step 2:
        bool has_authorized_user = false;
        for (; it != l.end(); ++it)
        {
            output += indent + cmdtable[2] + "<" + *it + "@" + recp_loc + ">" + "\n";
            auto rc = resp_no_user(recp_loc, *it);
            if (rc == 250)
                has_authorized_user = true;
            output += indent + to_string(rc) + "\n";
        }

        if (has_authorized_user)
        {
            // step 3:
            output += indent + cmdtable[3] + "\n";
            output += indent + to_string(resp_normal(3)) + "\n";

            // step 4:
            output += msg + indent + ".\n";
            output += indent + to_string(resp_normal(4)) + "\n";
        }
        // step 5:
        output += indent + cmdtable[5] + "\n";
        output += indent + to_string(resp_normal(5)) + "\n";

        // print
        cout << output;
    }
}
void init_MTAs();
unique_ptr<senderMTA> create_senderMTA();

int main()
{
    ios_base::sync_with_stdio(false);
    init_MTAs();
    while (auto p_mta = create_senderMTA())
        p_mta->send();

    return 0;
}

//////////////////////////////////////////////////////////////

void init_MTAs()
{
    string MTAheader, location;
    int num_user;
    while (cin >> MTAheader && MTAheader == "MTA")
    {
        cin >> location >> num_user;
        unordered_set<user_t> setu;
        for (auto i = 0; i < num_user; ++i)
        {
            user_t u; cin >> u;
            setu.insert(std::move(u));
        }
        MTAs.insert({std::move(location), std::move(setu)});
    }
}

pair<user_t, loc_t> parse_id(const string &s)
{
    auto it = s.find('@');
    return {s.substr(0, it), s.substr(it+1)};
}

unique_ptr<senderMTA> create_senderMTA()
{
    // unique_ptr<senderMTA> ret(nullptr);
    string sender; cin >> sender;
    if (sender == "*")
        return nullptr;

    // as long as there are still senders/receivers
    auto sender_id = parse_id(sender);

    recplist locNusers;
    unordered_map<loc_t, recplist::size_type> loc2index;
    vector<unordered_set<user_t>> loc2user;
    string user2mta;
    while (cin >> user2mta && user2mta != "*")
    {
        auto recp_id = parse_id(user2mta);
        auto it = loc2index.find(recp_id.second);
        if ( it != loc2index.end())
        {
            if (loc2user[it->second].insert(recp_id.first).second)
                locNusers[it->second].push_back(std::move(recp_id.first));
        }
        else
        {
            locNusers.emplace_back(vector<string>{recp_id.second, recp_id.first});
            loc2index[recp_id.second] = locNusers.size()-1;
            loc2user.push_back(unordered_set<user_t>{recp_id.first});
        }
    }

    // get msg
    if (user2mta == "*")    // starting * on a line by itself
        cin.ignore(100, '\n');

    contnt msg;
    string line;
    while (getline(cin, line) && line.at(0) != '*')
        msg += "     "+line+"\n";

    return unique_ptr<senderMTA>(new senderMTA(std::move(sender_id.first), std::move(sender_id.second), std::move(locNusers), std::move(msg)));
}



