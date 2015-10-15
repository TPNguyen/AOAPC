#include <iostream>
using namespace std;

int main()
{
    long long N, Sp, Sq;
    long long K = 0, A, B;
    while (cin >> N >> Sp >> Sq)
    {
        long long min_len = 0;
        int minA = 0, minB = 0;
        if (N > 1)
        {
            // find the smallest A first
            auto dif = Sq-Sp;
            for (A = 0; ; ++A)
            {
                if ((Sp << A) >= dif)
                    break;
            }

            minA = A;
            min_len = ((Sp+ (Sp<<minA))*(N-1)) >> minB;
            {
                for (; A < 32; ++A)
                {
                    for (B = 0; (Sp+ (Sp<<A))>>B >= Sq*2; ++B)
                        ;
                    long long new_len = ((Sp+ (Sp<<A))*(N-1)) >> B;
                    if ((Sp+ (Sp<<A)) == Sq << B)
                    {
                        min_len = new_len;
                        minA = A; minB = B;
                        break;
                    }
                    else
                    {
                        if (new_len < min_len)
                        {
                            min_len = new_len;
                            minA = A; minB = B;
                        }
                    }
                }
            }
        }
        cout << min_len + Sq << " " << minA << " " << minB << "\n";

        /*typedef long long LL;
        LL best=(LL)1<<62,a,b,aa=0,bb=0;
        for(a=0;a<32;++a)
            for(b=0;b<32;++b){
                LL cur=(((N-1)*Sp+((N-1)*Sp<<a))>>b)+Sq;
                if(cur>=N*Sq&&cur<best) best=cur,aa=a,bb=b;
            }
        if (best != min_len+Sq || aa != minA || bb != minB)
        {
            cout << N << " " << Sp << " " << Sq << "\n";
            cout << min_len + Sq << " " << minA << " " << minB << "\n";
            cout << best << " " << aa << " " << bb << "\n";
            break;
        }*/
    }

    return 0;
}
