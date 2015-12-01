// This version (memory pool) has run time error which I don't care to debug anymore.
// v2: uses raw pointer
#include <cstdio>
#include <cstring>

struct Node{
    char type;  //'p' means parent; 'e' means empty; 'f' means full
    int nextQuad;
    int num_black;
    Node* quads[4];
}tree[2048];
int tree_index = 0;

Node* Build();
//Node* build(const std::string& nodes, int& start, int depth);
int merge(Node* pic1, Node* pic2);
void inOrder(Node* root);

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
        tree_index = 0;
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
    Node* stack[2048];
    int top = 0;
    // read in a line representing nodes
    scanf("%s", nodes);
    int num_nodes = strlen(nodes);
    // Creating root
    Node* root = &tree[tree_index++];
    root->quads[3] = root->quads[2] = root->quads[1] = root->quads[0] = NULL;
    root->type = nodes[0];
    root->nextQuad = 0;
    if(nodes[0] == 'p')
        stack[++top] = root;
    else
        root->num_black = (nodes[0] == 'f'? 1024:0);

    for(int i = 1; i < num_nodes; ++i)
    {
        // current parent is done
        while(stack[top]->nextQuad == 4)    
        {
            int b = 0;
            for(int i = 0; i < 4; ++i)
                b += stack[top]->quads[i]->num_black;
            stack[top]->num_black = b;
            --top;
        }

        // Creating new node and attach to tree.back(). 
        // tree.back() node is guaranteed not to be full since if it was, it should have already been poped out in the code above.
        // No node with full children is left in the stack.
        Node* pNode = &tree[tree_index++];
        pNode->quads[3] = pNode->quads[2] = pNode->quads[1] = pNode->quads[0] = NULL;
        pNode->type = nodes[i];
        pNode->nextQuad = 0;
        if(nodes[i] == 'p')
        {
            stack[top]->quads[stack[top]->nextQuad++] = pNode;
            stack[++top] = pNode;
        }
        else
        {
            // black
            if(nodes[i] == 'f')
                pNode->num_black = 1<<(10-2*top);
            // white
            else
                pNode->num_black = 0;
            stack[top]->quads[stack[top]->nextQuad++] = pNode;
        }
    }

    while(top)
    {
        // current parent is done
        int b = 0;
        for(int i = 0; i < 4; ++i)
            b += stack[top]->quads[i]->num_black;
        stack[top]->num_black = b;
        --top;
    }

    inOrder(root);
    printf("\n");

    return root;
}

void inOrder(Node* root)
{
    if(root == NULL) return;
    printf("%c(%d)", root->type, root->num_black);
    for(int i = 0; i < 4; ++i)
        inOrder(root->quads[i]);
}



