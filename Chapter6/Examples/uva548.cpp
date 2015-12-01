#include <iostream>
#include <utility>
#include <limits>
#include <cstdlib>

struct node{
    int val;
    node* left;
    node* right;
};
std::pair<int, int> min_sum(std::numeric_limits<int>::max(),std::numeric_limits<int>::max());

void dfs(node* root, int sum);
node* build(int len, int* Inorder, int* Postorder);

int main()
{
    std::ios_base::sync_with_stdio(false);
    int Inorder[10000];
    int Postorder[10000];

    std::string line;
    // std::cout << min_sum.first << " " << min_sum.second << "\n";
    while(std::getline(std::cin, line))
    {
        // In Order Traversal
        char* pPrev = NULL;
        char* pEnd;
        Inorder[0] = strtol(line.data(), &pEnd, 10);
        int i = 1;
        do{
            pPrev = pEnd;
            Inorder[i++] = strtol(pPrev, &pEnd, 10);
        }while(pEnd > pPrev);
        --i;

        /*for(int kk = 0; kk < i; ++kk)   std::cout << Inorder[kk] << " ";
          std::cout << std::endl;*/

        // Post order traversal
        std::getline(std::cin, line);
        pPrev = NULL;
        Postorder[0] = strtol(line.data(), &pEnd, 10);
        int j = 1;
        do{
            pPrev = pEnd;
            Postorder[j++] = strtol(pPrev, &pEnd, 10);
        }while(pEnd > pPrev);
        --j;

        /*for(int kk = 0; kk < i; ++kk)   std::cout << Postorder[kk] << " ";
          std::cout << std::endl;*/

        /*if(i != j)
          std::cout << "Input format error!\n";*/

        // Build tree
        node* root = build(i, Inorder, Postorder);

        // Depth first search
        dfs(root, 0);
        std::cout << min_sum.second << "\n";
        min_sum.first = std::numeric_limits<int>::max();
    }

    return 0;
}

node* build(int len, int* Inorder, int* Postorder)
{
    if(len == 0)
        return NULL;

    int i, val = Postorder[len-1];
    for(i = 0; i < len; ++i)
        if(Inorder[i] == val)
            break;
    node* root = new node;
    root->val = val;
    root->left = build(i, Inorder, Postorder);
    root->right = build(len-1-i, Inorder+i+1, Postorder+i);

    return root;
}

void dfs(node* root, int sum)
{
    sum += root->val;
    // std::cout << root->val << "(" << sum << ") ";

    if(root->left == NULL && root->right == NULL)
    {
        if(sum < min_sum.first)
        {
            min_sum.first = sum;
            min_sum.second = root->val;
        }
        else if(sum == min_sum.first && min_sum.second > root->val)
            min_sum.second = root->val;

        return;
    }

    if(root->left != NULL)
    {
        dfs(root->left, sum);
    }
    if(root->right != NULL)
    {
        dfs(root->right, sum);
    }
}
