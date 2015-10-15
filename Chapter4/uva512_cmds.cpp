#include <iostream>
#include <string>
#include <vector>

class cmd {
    friend bool simulate(const std::vector<cmd> &, int &, int &);
    friend std::istream& operator>> (std::istream &, cmd &);
    friend std::ostream& operator<< (std::ostream &, const cmd &);

    private:
        std::string cmd_header;
        std::vector<int> co_ord;
};

std::istream& operator>> (std::istream &is, cmd &c)
{
    is >> c.cmd_header;
    if (c.cmd_header == "EX")
    {
        c.co_ord.reserve(4);
        for (auto i = 0; i < 4; ++i)
        {
            auto t = 0;
            is >> t;
            c.co_ord.push_back(t);
        }
    }
    else
    {
        auto sz = 0;
        is >> sz;
        c.co_ord.reserve(sz);
        for (auto i = 0; i < sz; ++i)
        {
            auto t = 0;
            is >> t;
            c.co_ord.push_back(t);
        }
    }

    return is;
}

std::ostream& operator<< (std::ostream &os, const cmd &c)
{
    os << c.cmd_header << " ";
    for (auto i: c.co_ord)
        os << i << " ";

    os << "\n";
}


bool simulate(const std::vector<cmd> &cmds, int &r, int &c)
{
    for (const auto &a_cmd : cmds) {
        // std::cout << a_cmd;
        if (a_cmd.cmd_header == "EX")
        {
            if (a_cmd.co_ord[0] == r && a_cmd.co_ord[1] == c)
            {
                r = a_cmd.co_ord[2];
                c = a_cmd.co_ord[3];
            }
            else if (a_cmd.co_ord[2] == r && a_cmd.co_ord[3] == c)
            {
                r = a_cmd.co_ord[0];
                c = a_cmd.co_ord[1];
            }
        } else
        {
            if (a_cmd.cmd_header == "DR")
            {
                auto dr = 0;
                for (auto i : a_cmd.co_ord)
                {
                    if (i == r) return false;
                    if (i < r) --dr;
                }
                r += dr;
            }
            else if (a_cmd.cmd_header == "DC")
            {
                auto dc = 0;
                for (auto i : a_cmd.co_ord)
                {
                    if (i == c) return false;
                    if (i < c) --dc;
                }
                c += dc;
            }
            else if (a_cmd.cmd_header == "IR")
            {
                auto dr = 0;
                for (auto i : a_cmd.co_ord)
                    if (i <= r) ++dr;

                r += dr;
            }
            else if (a_cmd.cmd_header == "IC")
            {
                auto dc = 0;
                for (auto i : a_cmd.co_ord)
                    if (i <= c) ++dc;

                c += dc;
            }
        }
        // std::cout << ">>> (" << r << "," << c << ")\n";
    }

    return true;
}

int main()
{
    int nr, nc, ncmds;
    int kase = 0;
    while (std::cin >> nr >> nc >> ncmds && nr)
    {
        std::vector<cmd> cmds(ncmds);
        for (auto i = 0; i < ncmds; ++i)
            std::cin >> cmds[i];

        if (kase)
            std::cout << "\n";
        std::cout << "Spreadsheet #" << ++kase << "\n";

        int r0, c0, nq;
        std::cin >> nq;
        while (nq--)
        {
            std::cin >> r0 >> c0;
            std::cout << "Cell data in (" << r0 << "," << c0 << ") ";

            if (simulate(cmds, r0, c0)) // not deleted
                std::cout << "moved to (" << r0 << "," << c0 << ")\n";
            else
                std::cout << "GONE\n";
        }
    }

    return 0;
}
