#include <iostream>
#include <string>
#include <cctype>
int main()
{
    int T = 0;
    std::cin >> T;
    while (T--)
    {
        std::string molecular;
        std::cin >> molecular;
        auto molar_mass = 0.0;

        auto prev_atom_weight = 0.0;
        int num_atom = 0;
        for(const auto c: molecular)
        {
            if (std::isalpha(c))
            {
                if (num_atom > 0)
                {
                    molar_mass += prev_atom_weight*(num_atom - 1);
                }
                switch (c)
                {
                    case 'C':
                        molar_mass += (prev_atom_weight = 12.01);
                        break;
                    case 'H':
                        molar_mass += (prev_atom_weight = 1.008);
                        break;
                    case 'O':
                        molar_mass += (prev_atom_weight = 16.0);
                        break;
                    case 'N':
                        molar_mass += (prev_atom_weight = 14.01);
                        break;
                    default:
                        std::cerr << "Unrecognized atom " << c << "\n";
                        break;
                }
                num_atom = 0;
            }
            else
                num_atom = num_atom*10 + c-'0';
        }
        if (num_atom > 0)
            molar_mass += prev_atom_weight*(num_atom - 1);

        std::cout.precision(3);
        std::cout << std::fixed << molar_mass << "\n";
    }

    return 0;
}
