// Shuffle, ACM/ICPC NWERC 2008, UVa 12174
// The idea is incorrect and code is incomplete. check uva12174_v2.cpp
//
int main()
{
    int T; cin >> T;
    while (T--)
    {
        int s, n; cin >> s >> n;
        vector<int> hist(n);
        for (auto i = 0; i < n; ++i)
            cin >> hist[i];

        vector<int> freq(s+1);
        auto I = 1; freq[hist[0]]++;
        for (; I < n; ++I)
        {
            if (I%s == 0)
                std::fill(freq.begin(), freq.end(), 0);
            if (freq[hist[I]]++)
                break;
        }

        bool impossible = false;
        vector<int> cnt1st(s);
        auto start = 0;
        if (I < n)
        {
            while (1)
            {
                auto jump = start;
                for (; hist[jump] == hist[start] && jump < I; jump += s)
                    ;
                if (jump < I)
                {
                    impossible = true;
                    break;
                }
                --freq[hist[start]];
                if (hist[start] != hist[I])
                {
                    ++cnt1st[hist[start]];
                    ++start;
                }
                else
                    break;
            }
        }

        // element i is the end of the current sliding window
        int valid_cnt = 0;
        if (!impossible)
        {
            for (; start < min(s,n); ++start)
            {
                if (cnt1st[hist[start]]++)
                    break;

                ++I;
                for (auto ns = I-start-1; I < n; ++I, ++ns)
                {
                    if (ns%s == 0)
                        std::fill(freq.begin(), freq.end(), 0);
                    if (freq[hist[I]]++)
                        break;
                }
                if (I < n)
                {
            while (1)
            {
                auto jump = start+1;
                for (; hist[jump] == hist[i] && jump < I; jump += s)
                    ;
                if (jump < I)
                {
                    impossible = true;
                    break;
                }
                --freq[hist[start]];
                if (hist[start] != hist[I])
                {
                    ++cnt1st[hist[start]];
                    ++start;
                }
                else
                    break;
            }


                }
                else
                    valid_cnt++;
            }
        }


            







