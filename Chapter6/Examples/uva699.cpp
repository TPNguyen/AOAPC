#include <iostream>
#include <map>
int buildTree(int x);

std::map<int, int> piles;
int main()
{
    std::ios_base::sync_with_stdio(false);
    int caseNum = 1;
    int root;
    while(1)
    {
        piles.clear();
        root = buildTree(0);
        if(root == -1)
            return 0;
        std::cout << "Case "<< caseNum++ << ":\n";
        std::map<int, int>::iterator it = piles.begin();
        std::cout << it->second;
        ++it;
        for(; it != piles.end(); ++it)
            std::cout << " " << it->second;
        std::cout << "\n\n";
    }
}

int buildTree(int x)
{
    int root = -1;
    std::cin >> root;
    if(root != -1)
    {
        piles[x] += root;
        buildTree(x-1);
        buildTree(x+1);
    }
    return root;
}
