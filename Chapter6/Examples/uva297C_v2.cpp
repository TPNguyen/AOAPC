#include <cstdio>
#include <cstring>
#include <vector>

struct Node{
    char type;  //'p' means parent; 'e' means empty; 'f' means full
    int nextQuad;
    int num_black;
    Node* quads[4];
    Node() {
        type = 'p';
        num_black = 0;
        nextQuad = 0;
        quads[0] = quads[1] = quads[2] = quads[3] = NULL;
    }
};

Node* Build();
// Node* build(const std::string& nodes, int& start, int depth);
int merge(Node* pic1, Node* pic2);
// void inOrder(Node* root);

int main()
{
    int num_cases;
    scanf("%d", &num_cases);

    while(num_cases--)
    {
        /*std::cin >> nodes;
          start = 0;
          depth = 0;
          Node* pic1 = build(nodes, start, depth);
          inOrder(pic1);
          std::cout << "\n";
          */
        Node* pic1 = Build();

        /*std::cin >> nodes;
          start = 0;
          depth = 0;
          Node* pic2 = build(nodes, start, depth);
          inOrder(pic2);
          std::cout << "\n";
          */
        Node* pic2 = Build();

        int blacks = merge(pic1, pic2);
        printf("There are %d black pixels.\n", blacks);
    }

    return 0;
}

int merge(Node* pic1, Node* pic2)
{
    // Leaf nodes.
    if(pic1->type == 'f')
        return pic1->num_black;
    if(pic2->type == 'f')
        return pic2->num_black;
    if(pic1->type == 'e')
        return pic2->num_black;
    if(pic2->type == 'e')
        return pic1->num_black;

    // both are of type 'p'
    int sum = 0;
    for(int i = 0; i < 4; ++i)
        sum += merge(pic1->quads[i], pic2->quads[i]);

    return sum;
}

/*Node* build(const std::string& nodes, int& start, int depth)
  {
  Node* root = new Node;
  root->type = nodes[start];
  if(nodes[start] != 'p')
  root->num_black = ((nodes[start] == 'f')? 1<<(10-2*depth): 0);
  else
  {
  for(int i = 0; i < 4; ++i)
  {
  root->quads[i] = build(nodes, ++start, depth+1);
  root->num_black += root->quads[i]->num_black;
  }
  }

  return root;
  }*/

Node* Build()
{
    char nodes[2048];
    std::vector<Node*> tree;

    // read in a line representing nodes
    scanf("%s", nodes);
    int num_nodes = strlen(nodes);
    // Creating root
    Node* root = new Node;
    root->type = nodes[0];
    if(nodes[0] == 'p')
        tree.push_back(root);
    else
        root->num_black = (nodes[0] == 'f'? 1024:0);

    for(int i = 1; i < num_nodes; ++i)
    {
        // current parent is done
        while(tree.back()->nextQuad == 4)    
        {
            int b = 0;
            for(int i = 0; i < 4; ++i)
                b += tree.back()->quads[i]->num_black;
            tree.back()->num_black = b;
            tree.pop_back();
        }

        // Creating new node and attach to tree.back(). 
        // tree.back() node is guaranteed not to be full since if it was, it should have already been poped out in the code above.
        // No node with full children is left in the stack.
        Node* pNode = new Node;
        pNode->type = nodes[i];
        if(nodes[i] == 'p')
        {
            tree.back()->quads[tree.back()->nextQuad++] = pNode;
            tree.push_back(pNode);
        }
        else
        {
            // black
            if(nodes[i] == 'f')
                pNode->num_black = 1<<(10-2*tree.size());
            // white
            else
                pNode->num_black = 0;
            tree.back()->quads[tree.back()->nextQuad++] = pNode;
        }
    }

    while(!tree.empty())
    {
        // current parent is done
        int b = 0;
        for(int i = 0; i < 4; ++i)
            b += tree.back()->quads[i]->num_black;
        tree.back()->num_black = b;
        tree.pop_back();
    }

    //    inOrder(root);
    //    std::cout << "\n";

    return root;
}

/*void inOrder(Node* root)
  {
  if(root == NULL) return;
  std::cout << root->type << "(" << root->num_black << ")";
  for(int i = 0; i < 4; ++i)
  inOrder(root->quads[i]);
  }*/


