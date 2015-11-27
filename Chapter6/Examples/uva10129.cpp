#include <iostream>
#include <string>
#include <cstring>

int vis[26];
int G[26][26];
void DFS(int parent, int* count);
int main()
{
    std::ios_base::sync_with_stdio(false);
    int num_tests, num_words;
    std::string word;

    int occurred[26] = {0};
    int degree[26] = {0};
    int num_nodes, connected_nodes, end1, end2;

    std::cin >> num_tests;
    for(int Cases = 0; Cases < num_tests; ++Cases)
    {
        std::cin >> num_words;
        num_nodes = 0, connected_nodes = 0;
        for(int i = 0; i < num_words; ++i)
        {
            std::cin >> word;
            end1 = word[0]-'a', end2 = word[word.size()-1]-'a';
            //In-degree
            degree[end1]++;
            //Out-degree
            degree[end2]--;
            // Graph
            G[end1][end2] = 1; G[end2][end1] = 1;
            // Count # of nodes in the graph
            if(!occurred[end1])
            {
                occurred[end1] = 1; num_nodes++;
            }       
            if(!occurred[end2])
            {
                occurred[end2] = 1; num_nodes++;
            }
        } 
        // Degree check
        bool ok = true;
        int num_Odd = 0;
        int oddDegree;
        for(int i = 0; i < 26; ++i)
        {
            // std::cout << degree[i] << std::endl;
            if(degree[i])
            {
                if(degree[i] > 1 || degree[i] < -1)
                {
                    // std::cout << 'a'+i << " Has degree " << degree[i] << std::endl;
                    ok = false;
                    break;
                }
                else
                {   // Can only have 2 odd degree nodes; Current odd degree has to be the negative of the previous one.
                    if(num_Odd == 2 || (num_Odd && oddDegree != -degree[i]))
                    {
                        // std::cout << "Num of odd: " << num_Odd << "; prev odd degree is: " << oddDegree << std::endl;
                        ok = false; break;
                    }
                    oddDegree = degree[i];
                    num_Odd++;
                }
            }
        }
        if(!ok)
            std::cout << "The door cannot be opened.\n";
        else
        {
            DFS(end1, &connected_nodes);
            if(connected_nodes == num_nodes)
                std::cout << "Ordering is possible.\n";
            else
                std::cout << "The door cannot be opened.\n";
        }
        // Clean up
        memset(degree, 0, sizeof(degree));
        memset(occurred, 0, sizeof(occurred));
        memset(vis, 0, sizeof(vis));
        memset(G, 0, sizeof(G));
    }

    return 0;
}

void DFS(int parent, int* count)
{
    vis[parent] = 1, (*count)++;
    for(int i = 0; i < 26; ++i)
    {
        if(G[parent][i] && !vis[i])
            DFS(i, count);
    }
}
