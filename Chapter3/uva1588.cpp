#include <iostream>
#include <string>

int main()
{
    std::string master, driven;
    while (std::cin >> master >> driven)
    {
        auto masterS = master.size(), drivenS = driven.size();
        int result = std::max(masterS, drivenS);

        // try shift to the right of the master
        decltype(masterS) to_right = 0;
        for (; to_right <= drivenS; ++to_right)
        {
            bool Ok = true;
            for (decltype(masterS) j = 0; j < masterS && j + to_right < drivenS; ++j)
                if (master[j]-'0' + driven[j+to_right]-'0' > 3)
                {
                    Ok = false;
                    break;
                }

            if (Ok)
                break;
        }

        int shift_right_result = masterS + to_right;

        if (shift_right_result > result)
        {
            // try shift to the right of the driven
            decltype(drivenS) to_left = 0;
            for (; to_left <= masterS; ++to_left)
            {
                bool Ok = true;
                for (decltype(drivenS) j = 0; j < drivenS && j + to_left < masterS; ++j)
                    if (driven[j]-'0' + master[j+to_left]-'0' > 3)
                    {
                        Ok = false;
                        break;
                    }

                if (Ok)
                    break;
            }

            int shift_left_result = drivenS + to_left;
            if (shift_left_result > result)
                result = std::min(shift_right_result, shift_left_result);
        }

        std::cout << result << "\n";
    }

    return 0;
}


