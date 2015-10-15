// Othello; ACM/ICPC World Finals 1992, Uva220

#include <iostream>
#include <tuple>
#include <iomanip>
#include <utility>

using namespace std;

constexpr int MAXN = 10;
int ListMoves(char cur, const char (&board)[MAXN][MAXN], bool print_result = true);
void PrintBoard(const char (&) [MAXN][MAXN]);
void PlaceDisk(int, int, char, char (&) [MAXN][MAXN]);

enum dir_comp {I = 0, J};
pair<int, int> dir[] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

int main()
{
    char board[MAXN][MAXN];

    int num_games; cin >> num_games;
    while(num_games--)
    {
        for (auto i = 1; i <= 8; ++i)
            for (auto j = 1; j <= 8; ++j)
                cin >> board[i][j];

        char cur_player; cin >> cur_player;

        int num_valid_moves = -1;
        while (true)
        {
            char cmd; cin >> cmd;
            if (cmd == 'L')
                num_valid_moves = ListMoves(cur_player, board);
            else if (cmd == 'Q')
            {
                PrintBoard(board);
                break;
            }
            else if (cmd == 'M')
            {
                char r, c; cin >> r >> c;
                int row = r - '0', col = c - '0';
                if (num_valid_moves == -1) // haven't determined if there is valid moves
                    num_valid_moves = ListMoves(cur_player, board, false);
                if (num_valid_moves == 0)
                    cur_player = cur_player == 'B' ? 'W' : 'B';

                PlaceDisk(row, col, cur_player, board);
                // clean up after a move
                cur_player = cur_player == 'B' ? 'W' : 'B';
                num_valid_moves = -1; // reset b/c cur_player is switched and board config is also changed
            }
        }
        if (num_games)
            cout << "\n";
    }

    return 0;
}

bool IsValidMove(const int i, const int j, const char cur, const char (&board)[MAXN][MAXN], int *flip_count = nullptr)
{
    char opponent = (cur == 'B'? 'W' : 'B');
    bool ret = false;
    for (auto idir = 0; idir < 8; ++idir)
    {
        auto deltaI = get<I>(dir[idir]), deltaJ = get<J>(dir[idir]);
        auto k = i + deltaI, l = j + deltaJ;
        auto count_oppo = 0;
        for ( ; k >=1 && k <= 8 && l >= 1 && l <= 8 && board[k][l] == opponent; k += deltaI, l += deltaJ)
            ++count_oppo;
        if (count_oppo && k >= 1 && k <= 8 && l >= 1 && l <= 8 && board[k][l] == cur)
        {
            if (flip_count != nullptr)
            {
                ret = true;
                flip_count[idir] = count_oppo;
            }
            else
                return true;
        }
    }

    return ret;
}

void FlipOppo(const int i, const int j, const char cur, char (&board)[MAXN][MAXN], int (&flip_count)[8])
{
    for (auto idir = 0; idir < 8; ++idir)
    {
        auto deltaI = get<I>(dir[idir]), deltaJ = get<J>(dir[idir]);
        auto k = i, l = j;
        while(flip_count[idir]--)
        {
            k += deltaI, l += deltaJ;
            board[k][l] = cur;
        }
    }
    board[i][j] = cur;
}

int ListMoves(char cur, const char (&board)[MAXN][MAXN], bool print_result)
{
    int num_legal = 0;
    for (auto i = 1; i <= 8; ++i)
        for (auto j = 1; j <= 8; ++j)
        {
            if (board[i][j] == '-')
            {
                if (IsValidMove(i, j, cur, board))
                {
                    if (print_result)
                    {
                        if (num_legal) cout << " ";
                        cout << "(" << i << "," << j << ")";
                    }
                    ++num_legal;
                }
            }
        }

    if (print_result)
    {
        if (num_legal == 0)
            cout << "No legal move.";
        cout << "\n";
    }

    return num_legal;
}
void PrintBoard(const char (&board) [MAXN][MAXN])
{
    for (auto i = 1; i <= 8; ++i)
    {
        for (auto j = 1; j <= 8; ++j)
            cout << board[i][j];

        cout << "\n";
    }
}

void PlaceDisk(const int r, const int c, const char cur, char (&b) [MAXN][MAXN])
{
    int flip_count[8] = {0};
    IsValidMove(r, c, cur, b, flip_count);
    FlipOppo(r, c, cur, b, flip_count);

    int num_black = 0, num_white = 0;
    for (auto i = 1; i <= 8; ++i)
        for (auto j = 1; j <= 8; ++j)
            if (b[i][j] == 'B')
                ++num_black;
            else if (b[i][j] == 'W')
                ++num_white;

    cout << "Black - " << setw(2) << num_black << " White - " << setw(2) << num_white << "\n";
}


/*tuple<bool, bool> HBracket(const int i, const int j, const char cur, const char (&board)[MAXN][MAXN])
{
    bool right = false, left = false;
    char opponent = (cur == 'B'? 'W' : 'B');
    auto k = j + 1;
    for ( ; k <= 8 && board[i][k] == opponent; ++k)
        ;
    if (k > j+1 && k <= 8 && board[i][k] == cur)
        right = true;

    k = j - 1;
    for ( ; k >= 1 && board[i][k] == opponent; --k)
        ;
    if (k < j-1 && k >= 1 && board[i][k] == cur)
        left = true;

    return {right, left};
}
tuple<bool, bool> VBracket(const int i, const int j, const char cur, const char (&board)[MAXN][MANX])
{
    bool down = false, up = false;
    char opponent = (cur == 'B'? 'W' : 'B');
    auto k = i + 1;
    for ( ; k <= 8 && board[k][j] == opponent; ++k)
        ;
    if (k > i+1 && k <= 8 && board[k][j] == cur)
        down = true;

    k = i - 1;
    for ( ; k >= 1 && board[k][j] == opponent; --k)
        ;
    if (k < i-1 && k >= 1 && board[k][j] == cur)
        up = true;

    return {down, up};
}
tuple<bool, bool, bool, bool> DBracket(const int i, const int j, const char cur, const char (&board)[MAXN][MAXN])
{
    bool downright = false, upleft = false, downleft = false, upright = false;
    char opponent = (cur == 'B'? 'W' : 'B');
    // major directions
    auto k = i + 1, l = j + 1;
    for ( ; k <= 8 && l <= 8 && board[k][l] == opponent; ++k, ++l)
        ;
    if (k > i+1 && k <= 8 && l <= 8 && board[k][l] == cur)
        downright = true;

    k = i - 1, l = j - 1;
    for ( ; k >= 1 && l >= 1 && board[k][l] == opponent; --k, --l)
        ;
    if (k < i-1 && k >= 1 && l >=1 && board[k][l] == cur)
        upleft = true;

    // minor directions
    k = i + 1, l = j - 1;
    for ( ; k <= 8 && l >= 1 && board[k][l] == opponent; ++k, --l)
        ;
    if (k > i+1 && k <= 8 && l >= 1 && board[k][l] == cur)
        downleft = true;

    k = i - 1, l = j + 1;
    for ( ; k >= 1 && l <= 8 && board[k][l] == opponent; --k, ++l)
        ;
    if (k < i-1 && k >= 1 && l <= 8 && board[k][l] == cur)
        upright = true;

    return {downright, upleft, downleft, upright};
}

bitset<8> IsValidMove(const int i, const int j, const char cur, const char (&board)[MAXN][MAXN])
{
    auto h = HBracket(i, j, cur, board);
    auto v = VBracket(i, j, cur, board);
    auto d = DBracket(i, j, cur, board);
    bitset<8> ret;
    ret.set(0, get<0>(h)); ret.set(1, get<1>(h));
    ret.set(2, get<0>(v)); ret.set(3, get<1>(v));
    ret.set(4, get<0>(d)); ret.set(5, get<1>(d));
    ret.set(6, get<2>(d)); ret.set(7, get<3>(d));

    return ret;
}*/

