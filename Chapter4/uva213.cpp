#include <iostream>
#include <cmath>
#include <string>

int get_seg_len();
bool get_next_key(int len_to_read, int &key_index);

int main()
{
    std::string header;
    while (std::getline(std::cin, header))
    {
        // msg = segments + 000
        // segment [segments]:
        //  segment = LLL + ... + 11...

        // Could have parsed the header and store [len, value] pair for the lookup
        // len is at most 7 and value is just 0 -> (2<<len)-2
        int seglen = 0;
        std::string result;
        while (seglen = get_seg_len())
        {
            int key = 0;
            int offset = (1 << seglen) - seglen - 1;
            while (get_next_key(seglen, key))
                result += header[offset + key];
                //std::cout << header[offset + key];
        }

        std::cout << result << "\n";
        std::cin.ignore(100, '\n');
    }

    return 0;
}

inline bool get_next_key(int len_to_read, int &key_index)
{
    key_index = 0;
    char c;
    int total_len = len_to_read;
    while (len_to_read--)
    {
        std::cin >> c;
        key_index += (c-'0') << (len_to_read);
    }

    if (key_index == (1<< total_len) -1) // all 1's
        return false;
    return true;
}

inline int get_seg_len()
{
    auto len = 0;
    char c;
    for (auto i = 0; i < 3; ++i)
    {
        std::cin >> c;
        len += (c-'0') << (2-i);
    }

    return len;
}
