// Gates, UVa 1607

#include <iostream>
#include <vector>
using namespace std;

struct Gate
{
    int sa, sb;
    int o;
};

int output(int num1s, vector<Gate> &net)
{
    for (auto &g: net)
    {
        int in1 = g.sa > 0 ? net[g.sa].o : ((-g.sa) <= num1s);
        int in2 = g.sb > 0 ? net[g.sb].o : ((-g.sb) <= num1s);
        g.o = !(in1 && in2);
    }

    return net.back().o;
}

int solve(int out0, int n, vector<Gate> &net)
{
    int lo = 1, hi = n+1;
    while (lo < hi)
    {
        int mid = lo + (hi-lo)/2;
        if (output(mid, net) != out0)
            hi = mid;
        else
            lo = mid+1;
    }

    return lo;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int D; cin >> D;
    while (D--)
    {
        int n, m; cin >> n >> m; // n: num of net inputs; m: num of gates
        // input the net
        vector<Gate> net(m+1);
        for (auto i = 1; i <= m; ++i)
            cin >> net[i].sa >> net[i].sb;

        int out0 = output(0, net);
        int out1 = output(n, net);

        if (out0 == out1)
        {
            for (auto i = 1; i <= n; ++i)
                cout << "0";
        }
        else
        {
            int xloc = solve(out0, n, net);
            for (auto i = 1; i < xloc; ++i)
                cout << "1";
            cout << "x";
            for (auto i = xloc+1; i <= n; ++i)
                cout << "0";
        }

        cout << "\n";
    }

    return 0;
}
