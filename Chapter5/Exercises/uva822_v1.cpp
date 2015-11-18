#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct topic{
    int tid,num,t0,t,dt,q_num,finished;
};
struct member{
    int pid,k,work_left,last;
    vector<int>pidk;
    bool operator <(const member&a) const{
        if(a.last==last) return a.pid>pid;
        else return a.last>last;
    }
};
vector<topic>topics;
vector<member>staff;
int main(){
    int m,n,kase=0;
    while(cin>>m&&m){
        int time=0,need=0;
        while(m--){
            topic a;
            cin>>a.tid>>a.num>>a.t0>>a.t>>a.dt;
            a.q_num=a.finished=0;
            topics.push_back(a);
        }
        cin>>n;
        int z=0;
        while(n--){
            z++;
            member a;
            int x;
            a.work_left=a.last=0;
            cin>>a.pid>>a.k;
            a.pid=z;
            for(int i=0;i<a.k;i++){
                cin>>x;
                a.pidk.push_back(x);
            }
            staff.push_back(a);
        }
        while(1){
            for(int i=0;i<topics.size();i++)
                if(time>=topics[i].t0&&topics[i].finished+topics[i].q_num<topics[i].num){
                    topics[i].t0+=topics[i].dt;
                    topics[i].q_num=min(++topics[i].q_num,topics[i].num-topics[i].finished);
                }
            sort(staff.begin(),staff.end());
            for(int i=0;i<staff.size();i++){
                if(!staff[i].work_left)
                    for(int j=0;j<staff[i].pidk.size();j++)
                        for(int k=0;k<topics.size();k++)
                            if(staff[i].pidk[j]==topics[k].tid&&topics[k].q_num){
                                staff[i].last=time;
                                staff[i].work_left=topics[k].t;
                                topics[k].q_num--;
                                need=max(need,topics[k].t);

                                if(++topics[k].finished==topics[k].num){
                                    topics.erase(topics.begin()+k);
                                    if(!topics.size()){
                                        time+=need;
                                        goto END;
                                    }
                                }
                                goto NEXT_P;
                            }
NEXT_P:
                continue;
            }
            time++;
            need=max(--need,0);
            for(int i=0;i<staff.size();i++)
                staff[i].work_left=max(--staff[i].work_left,0);
        }
END:
        kase++;
        cout<<"Scenario "<<kase<<": All requests are serviced within "<<time<<" minutes."<<endl;
        staff.clear();
        topics.clear();
    }
    return 0;
}
