#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int r0,c0,r1,c1,r2,c2,dir;

struct Node{
    int r; //縱軸
    int c; //橫軸
    int dir; //進入方向
    Node(int r=0, int c=0, int dir=0):r(r),c(c),dir(dir){} //(r,c,dir)
};

void print_ans(Node u);

const char* dirs = "NESW";
const char* turns = "FLR";
//dir_id將回傳[c這個字母在dirs字串中的位址 - dirs的開頭位址]
//即是回傳c在dirs中是第幾項
//turn_id如法炮製
int dir_id(char c) {return strchr(dirs,c) - dirs;} 
int turn_id(char c) {return strchr(turns,c) - turns;} 

// 方向編號圖如下:
//     0
//   3   1
//     2
const int dr[]={-1,0,1,0};
const int dc[]={0,1,0,-1};
//行走函數，根據目前狀態和轉彎方式，回傳下一個節點的值
Node walk(const Node& u, int turn){
    int dir = u.dir;
    if(turn == 1)dir = (dir+3) %4; //若turn為L(在turns位置為1)則逆時針
    if(turn == 2)dir = (dir+1) %4; //若turn為R(turns位置為2)則順時針
    return Node(u.r+dr[dir], u.c+dc[dir], dir); //回傳新的節點
}

//確保下一點是存在的節點
bool inside(int r, int c){
    return  r>=1 && r<=9 && c>=1 && c<=9;

}


int d[10][10][4]; //初始狀態到(r,c,dir)的最短路徑長度
Node p[10][10][4]; //(r,c,dir)之父節點
int has_edge[10][10][4][3]; 
//路標，has_edge[r][c][dir][turn]表示(r,c,dir)是否可沿turn方向行走

void solve(){
    queue<Node> q;
    memset(d,-1,sizeof(d));
    Node u(r1,c1,dir);
    d[u.r][u.c][u.dir]=0;
    q.push(u);
    while(!q.empty()){
        Node u = q.front(); q.pop();
        if(u.r == r2 && u.c == c2) {
            print_ans(u); return;
        }
        for(int i=0;i<3;i++){
            Node v = walk(u,i);
            if(has_edge[u.r][u.c][u.dir][i] && inside(v.r, v.c)
                    && d[v.r][v.c][v.dir] <0){
                d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] +1 ;
                p[v.r][v.c][v.dir] = u;
                q.push(v);
            }
        }
    }
    printf("  No Solution Possible\n");
}

void print_ans(Node u){
    vector<Node> nodes;
    for(;;){
        nodes.push_back(u);
        if(d[u.r][u.c][u.dir] ==0) break;
        u = p[u.r][u.c][u.dir];
    }
    nodes.push_back(Node(r0,c0,dir)); //放入出發點

    int count = 0;
    for(int i=nodes.size()-1; i>=0; i--){
        if(count%10 == 0)printf(" ");
        printf(" (%d,%d)", nodes[i].r, nodes[i].c);
        if(++count %10 == 0)printf("\n");
    }
    if(nodes.size() %10 !=0) printf("\n");
}

int main(){
    string maze_name;
    while(1){
        cin >> maze_name;
        if(maze_name == "END")break;
        else cout << maze_name << '\n';

        memset(has_edge,0,sizeof(has_edge));
        //memset(p,0,sizeof(p));

        char input_dir[99];
        scanf("%d%d%s%d%d",&r0,&c0,input_dir,&r2,&c2);
        dir = dir_id(input_dir[0]);
        r1 = r0+dr[dir];
        c1 = c0+dc[dir];

        while(1){
            int input_r,input_c;
            scanf("%d",&input_r);
            if(input_r==0)break;
            scanf("%d",&input_c);
            //printf("%d %d\n",input_r,input_c);
            char input_flag[100];
            while(scanf("%s",input_flag)==1 && input_flag[0]!='*'){
                //cout << input_flag;
                for(int i=1;i<strlen(input_flag);i++){
                    has_edge[input_r][input_c][dir_id(input_flag[0])][turn_id(input_flag[i])]=1;
                }
            }
        }
        solve();
    }

    return 0;
}
