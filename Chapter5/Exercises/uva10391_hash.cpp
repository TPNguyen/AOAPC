// http://blog.csdn.net/a1061747415/article/details/25920267

#include <iostream>
#include <functional>
#include <string>
#include <cstdio>
#include <set>
#include <cstring>
using namespace std;

const int maxn=1000003;

int head[maxn],nextt[maxn];
string str[maxn];
int cnt;
// set<int> wordlens;

hash <string> str_hash;

inline void initial(){
    ios_base::sync_with_stdio(false);
    // cnt=0;
    // for(int i=0;i<maxn;i++) head[i]=-1;
    memset(head, -1, sizeof(head));
}

inline void add(string &st){
    // wordlens.insert(st.size());
    int c=str_hash(st)%maxn;
    str[cnt]=std::move(st);
    nextt[cnt]=head[c];
    head[c]=cnt++;
}

inline bool canfind(const string &st){
    int c=str_hash(st)%maxn;
    for(int i=head[c];i!=-1;i=nextt[i]){
        if(str[i]==st) return true;
    }
    return false;
}

int main(){
    initial();
    string st;
    while(cin>>st) add(st);
    for(auto i = 0; i < cnt; ++i){
        //for (const auto &l: wordlens)
        for (int l = 1; l<str[i].size(); ++l)
        {
            // if (l >= str[i].size())
                // break;
            // string sub1=str[i].substr(0,k);
            // string sub2=str[i].substr(k,str[i].length()-k);
            if(canfind(str[i].substr(0, l))  &&  canfind(str[i].substr(l))){
                cout << str[i] << "\n";
                break;
            }
        }
    }
    return 0;
}
