#include <cstdio>

int main()
{
    int num = 1;
    int depth;
    int vorder[7];
    int vva[7];
    int vleaf[128];
    while(scanf("%d ", &depth))
    {
        if(depth == 0) return 0;

        int num_vva;
        char c = getchar();         // remove x
        for(int i = 0; i < depth - 1; ++i)
            scanf("%d x", &vorder[i]);

        scanf("%d ", &vorder[depth-1]);
        for(int i = 0; i < (1<<depth); ++i)
            vleaf[i] = getchar() - '0';

        printf("S-Tree #%d:\n", num++);
        scanf("%d", &num_vva);
        for(int i = 0; i < num_vva; ++i)
        {
            getchar();      // remove newline
            for(int j = 0; j < depth; ++j)
                vva[j] = getchar() - '0';
            int index = vva[vorder[0]-1];
            for(int j = 1; j < depth; ++j)
            {
                index <<= 1;
                index += vva[vorder[j]-1];
            }
            printf("%d", vleaf[index]);
        }
        printf("\n\n");
    }

    return 0;
}

