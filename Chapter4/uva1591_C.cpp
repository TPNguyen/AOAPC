#include<cstdio>
typedef long long LL;
int main(){
    LL n,sp,sq;
    while(~scanf("%lld%lld%lld",&n,&sp,&sq)){
        LL best=(LL)1<<62,a,b,aa=0,bb=0;
        for(a=0;a<32;++a)
            for(b=0;b<32;++b){
                LL cur=(((n-1)*sp+((n-1)*sp<<a))>>b)+sq;
                if(cur>=n*sq&&cur<best) best=cur,aa=a,bb=b;
            }
        printf("%lld %lld %lld\n",best,aa,bb);
    }
    return 0;
}
