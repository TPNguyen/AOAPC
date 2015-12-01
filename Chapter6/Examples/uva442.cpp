#include <iostream>
#include <stack>
#include <utility>

int main()
{
    std::ios_base::sync_with_stdio(false);
    int num_matrix;
    std::cin >> num_matrix;

    std::pair<int, int> dim[num_matrix];

    for(int i = 0; i < num_matrix; ++i)
    {
        char c;
        int row, col;
        std::cin >> c >> row >> col;
        dim[c-'A'].first = row;
        dim[c-'A'].second = col;
    }

    std::string line;
    while(std::cin >> line)
    {
        int cost = 0;
        bool Error = false;
        std::stack<std::pair<int, int> > st;
        for(int i = 0; i < line.size(); ++i)
        {
            if(line[i] != ')' && line[i] != '(')    st.push(dim[line[i]-'A']);
            else if(line[i] == ')')
            {
                std::pair<int, int> op1, op2;
                op2 = st.top(); st.pop();
                op1 = st.top(); st.pop();
                if(op1.second != op2.first)
                {
                    std::cout << "error\n";
                    Error = true;
                    break;
                }

                cost += op1.first * op1.second * op2.second;
                st.push(std::make_pair(op1.first, op2.second));
            }
        }
        if(!Error)
            std::cout << cost << "\n";
    }

    return 0;
}
