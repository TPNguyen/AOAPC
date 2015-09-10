#include <iostream>
#include <sstream>
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

        std::istringstream is(molecular);
        auto molar_mass = 0.0;
        char atom;
        int num_atom = 0;
        double prev_atom_weight = 0.0;
        while (is >> atom)
        {
            switch (atom)
            {
                case 'C':
                    prev_atom_weight = 12.01;
                    break;
                case 'H':
                    prev_atom_weight = 1.008;
                    break;
                case 'O':
                    prev_atom_weight = 16.0;
                    break;
                case 'N':
                    prev_atom_weight = 14.01;
                    break;
                default:
                    std::cerr << "Unrecognized atom " << atom << "\n";
                    break;
            }
            if (std::isdigit(is.peek()))
            {
                is >> num_atom;
                molar_mass += prev_atom_weight * num_atom;
            }
            else
                molar_mass += prev_atom_weight;
        }

        std::cout.precision(3);
        std::cout << std::fixed << molar_mass << "\n";
    }

    return 0;
}

