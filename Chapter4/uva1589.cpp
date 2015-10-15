// Xiangqi (Chinese Chess)

#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <utility>
#include <cstdlib>

using namespace std;
using rowcol = pair<int, int>;
using red_pieces_t = pair<char, rowcol>;

vector<pair<int, int>> get_next_moves(int bg_row, int bg_col)
{
    vector<pair<int, int>> ret;
    int row_delta[] = {-1, 1};
    int col_delta[] = {-1, 1};

    for (auto c: row_delta)
    {
        if (bg_row + c >= 1 && bg_row + c <= 3)
            ret.emplace_back(bg_row + c, bg_col);
    }
    for (auto c: col_delta)
    {
        if (bg_col + c >= 4 && bg_col + c <= 6)
            ret.emplace_back(bg_row, bg_col + c);
    }

    return ret;
}

bool on_same_row(const rowcol &lhs, const rowcol &rhs)
{
    return lhs.first == rhs.first;
}
bool on_same_col(const rowcol &lhs, const rowcol &rhs)
{
    return lhs.second == rhs.second;
}
bool in_between(const rowcol &a, const rowcol &b, const rowcol &target)
{
    if (on_same_row(a, b) && on_same_row(a, target))
    {
        if ((a.second < target.second && target.second < b.second) ||
            (b.second < target.second && target.second < a.second))
            return true;
    }
    else if (on_same_col(a, b) && on_same_col(a, target))
    {
        if ((a.first < target.first && target.first < b.first) ||
            (b.first < target.first && target.first < a.first))
            return true;
    }
    return false;
}

int num_intervening(const rowcol &src, const rowcol &dst, const int N, const array<red_pieces_t, 10> &red_pieces)
{
    int ret = -1;
    if (src != dst && (on_same_row(src, dst) || on_same_col(src, dst)))
    {
        ret = 0;
        for (auto i = 0; i < N; ++i)
        {
            if (in_between(src, dst, get<1>(red_pieces[i])))
                ++ret;
            if (ret > 1)
                break;
        }
    }

    return ret;
}

bool checkmate_by_general(const rowcol &m, const int N, const array<red_pieces_t, 10> &red_pieces, const int index)
{
    auto crloc = get<1>(red_pieces[index]);
    if (num_intervening(crloc, m, N, red_pieces) == 0)
        return true;

    return false;
}

bool checkmate_by_chariot(const rowcol &m, const int N, const array<red_pieces_t, 10> &red_pieces, const int index)
{
    auto crloc = get<1>(red_pieces[index]);
    if (m != crloc)
    {
        if (num_intervening(crloc, m, N, red_pieces) == 0)
            return true;
    }

    return false;
}
bool checkmate_by_cannon(const rowcol &m, const int N, const array<red_pieces_t, 10> &red_pieces, const int index)
{
    auto crloc = get<1>(red_pieces[index]);
    if (m != crloc)
    {
        if (num_intervening(crloc, m, N, red_pieces) == 1)
            return true;
    }

    return false;
}
bool checkmate_by_horse(const rowcol &m, const int N, const array<red_pieces_t, 10> &red_pieces, const int index)
{
    auto crloc = get<1>(red_pieces[index]);
    auto hobblepoint = crloc;
    if (abs(crloc.first - m.first) == 1)
    {
        if (m.second - crloc.second == 2)
            ++hobblepoint.second;
        else if(m.second - crloc.second == -2)
            --hobblepoint.second;
    }
    else if (abs(crloc.second - m.second) == 1)
    {
        if (m.first - crloc.first == 2)
            ++hobblepoint.first;
        else if (m.first - crloc.first == -2)
            --hobblepoint.first;
    }

    if (hobblepoint == crloc)
        return false;
    for (auto i = 0; i < N; ++i)
        if (hobblepoint == get<1>(red_pieces[i]))
            return false;

    return true;
}

bool red_piece_can_occupy(const rowcol &m, const int N, const array<red_pieces_t, 10> &red_pieces)
{
    for(auto i = 0; i < N; ++i)
    {
        auto ptype = get<0>(red_pieces[i]);
        if(ptype == 'G')
        {
            if (checkmate_by_general(m, N, red_pieces, i))
                return true;
        }
        else if (ptype == 'R') // chariot
        {
            if (checkmate_by_chariot(m, N, red_pieces, i))
                return true;
        }
        else if (ptype == 'C') // cannon
        {
            if (checkmate_by_cannon(m, N, red_pieces, i))
                return true;
        }
        else if (ptype == 'H') // horse
        {
            if (checkmate_by_horse(m, N, red_pieces, i))
                return true;
        }
    }

    return false;
}

int main()
{
    int N, bg_row, bg_col; // bg == black general
    array<red_pieces_t, 10> red_pieces;
    while (std::cin >> N >> bg_row >> bg_col && N)
    {
        int red_general_i = -1;
        for (auto i = 0; i < N; ++i)
        {
            char t;
            int rr, rc;
            cin >> t >> rr >> rc;
            red_pieces[i] = make_pair(t, make_pair(rr, rc));
            if (t == 'G')
                red_general_i = i;
        }

        vector<rowcol> bg_next_moves = get_next_moves(bg_row, bg_col);

        bool is_checkmate = true;
        if (red_general_i > 0 && num_intervening({bg_row, bg_col}, get<1>(red_pieces[red_general_i]), N, red_pieces) == 0)
            is_checkmate = false;
        else
        {
            for (const auto &m: bg_next_moves)
            {
                if (!red_piece_can_occupy(m, N, red_pieces))
                {
                    is_checkmate = false;
                    break;
                }
            }
        }

        if (is_checkmate)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
