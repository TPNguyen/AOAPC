#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_valid(const string &p, string &c, bool evenp);
void print_content(const string &content);

int main()
{
    int num_disk, block_size, total_blocks;
    int Kase = 0;
    while (cin >> num_disk >> block_size >> total_blocks && num_disk)
    {
        ++Kase;
        char EO; cin >> EO;
        bool even_parity = EO == 'E' ? true : false;

        vector<string> bits(num_disk);
        for (auto i = 0; i < num_disk; ++i)
            cin >> bits[i];

        bool disk_corrupted = false;
        string content;
        for (auto on_block = 0, parity_on_disk = 0; on_block < total_blocks; ++on_block, ++parity_on_disk)
        {
            parity_on_disk %= num_disk;
            string parity = bits[parity_on_disk].substr(on_block*block_size, block_size);
            string block_all_dsk;
            for (auto on_disk = 0; on_disk < num_disk; ++on_disk)
            {
                if (on_disk == parity_on_disk) continue;
                block_all_dsk += bits[on_disk].substr(on_block*block_size, block_size);
            }
            if (is_valid(parity, block_all_dsk, even_parity))
                content += block_all_dsk;
            else
            {
                disk_corrupted = true;
                break;
            }
        }

        if (disk_corrupted)
            cout << "Disk set " << Kase << " is invalid.\n";
        else
        {
            cout << "Disk set " << Kase << " is valid, contents are: ";
            print_content(content);
        }

    }

    return 0;
}

bool is_valid(const string &p, string &c, bool evenp)
{
    auto bs = p.size();
    auto cs = c.size();
    for (auto i = 0; i < bs; ++i)
    {
        auto count1s = 0; auto countxs = 0;
        auto recover = -1;
        if (p[i] == '1') ++count1s;
        else if (p[i] == 'x') ++countxs;

        for (auto j = i; j < cs; j += bs)
        {
            if (c[j] == '1')
                ++count1s;
            else if (c[j] == 'x')
            {
                ++countxs;
                recover = j;
            }
        }

        if ((countxs == 0 && (count1s % 2 == 0) != evenp) || countxs > 1)
            return false;
        if (recover >= 0)
            c[recover] = '0' + ((count1s % 2 == 0) != evenp);
    }

    return true;
}

void print_content(const string &content)
{
    auto i = 0;
    auto hex_dgt = 0;
    cout << hex << uppercase;
    for ( ; i + 4 < content.size(); i += 4)
    {
        hex_dgt = 0;
        for (auto j = 0; j < 4; ++j)
            hex_dgt += (content[i+j] - '0') << (3-j);

        cout << hex_dgt;
    }

    hex_dgt = 0;
    for (auto j = 0; j < content.size() - i; ++j)
        hex_dgt += (content[i+j] - '0') << (3-j);
    cout << hex_dgt;

    cout << "\n";

    cout << dec << nouppercase;
}
