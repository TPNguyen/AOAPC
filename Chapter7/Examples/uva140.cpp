// Bandwidth, UVa 140
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

const int MAXNODE = 8;
const int MAXBAND = 1024;
int G[MAXNODE][MAXNODE];
// int degrees[MAXNODE];
int occur[30];
std::vector<int> nodes;
std::vector<int> bestOrder;
int minBandw;

void findBandW(const std::vector<int> &perm);
bool readG()
{
    minBandw = MAXBAND;
    char end1, end2;
    while(1)
    {
        std::cin >> end1;
        if(end1 == '#') return false;
        std::cin.ignore(); // the ':' character
        if(!occur[end1-'A'])
        {
            occur[end1-'A'] = 1;
            nodes.push_back(end1-'A');
        }
        do{
            std::cin.get(end2);
            if(end2 == '\n')
                return true;
            if(end2 == ';')
                break;
            else
            {
                if(!occur[end2-'A'])
                {
                    occur[end2-'A'] = 1;
                    nodes.push_back(end2-'A');
                }
                // nodes[end2] = 1;
                G[end1-'A'][end2-'A'] = 1;
                G[end2-'A'][end1-'A'] = 1;
            }
        }while(1);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    while(readG())
    {
        std::sort(nodes.begin(), nodes.end());
        // A B C F G D H E -> 3
        /*nodes[0] = 0, nodes[1] = 1, nodes[2] = 2,
          nodes[3] = 5, nodes[4] = 6, nodes[5] = 3,
          nodes[6] = 7, nodes[7] = 4;*/
        do{
            findBandW(nodes);
        }while(std::next_permutation(nodes.begin(), nodes.end()));

        // Output best permutation and its corresponding bandwidth
        for(int i = 0; i < bestOrder.size(); ++i)
            std::cout << (char)(bestOrder[i]+'A') << " ";
        std::cout << "-> " << minBandw << "\n";

        memset(G, 0, sizeof(G));
        memset(occur, 0, sizeof(occur));
        nodes.clear();
    }

    return 0;
}

void findBandW(const std::vector<int> &perm)
{
    int maxBandw = 0;
    for(int i = 0; i < perm.size()-1; ++i)
    {
        if(i + maxBandw >= perm.size()-1)
            break;
        int bandwidth = 0;
        for(int j = perm.size()-1; j > i; --j)
        {
            if(G[perm[i]][perm[j]])
            {
                if(j-i > bandwidth)
                    bandwidth = j-i;
                break;
            }
        }

        if(bandwidth >= minBandw)
            return;
        if(bandwidth > maxBandw)
            maxBandw = bandwidth;
    }

    minBandw = maxBandw;
    bestOrder = perm;
}
