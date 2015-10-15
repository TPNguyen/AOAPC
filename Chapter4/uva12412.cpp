#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <list>

constexpr double eps = 1e-5;
enum score_index { Chinese, Math, English, Prog, Size };
struct Student {
    long long SID;
    std::string name;
    int CID;
    // int sChinese, sMath, sEnglish, sProg;
    int scores[score_index::Size];
    int total;
    double average;
    Student() = default;
    Student(long long pSID, const std::string &pName, int pCID, int psC, int psM, int psE, int psP)
        : SID(pSID), name(pName), CID(pCID)
    {
        scores[score_index::Chinese] = psC;
        scores[score_index::Math] = psM;
        scores[score_index::English] = psE;
        scores[score_index::Prog] = psP;
        total = psC + psM + psE + psP;
        average = static_cast<double>(total)/4;
    }
};

std::list<Student> allStudents;

void display()
{
    static std::string menu[] = {"1 - Add\n", "2 - Remove\n", "3 - Query\n", "4 - Show ranking\n", "5 - Show Statistics\n", "0 - Exit\n" };
    std::cout << "Welcome to Student Performance Management System (SPMS).\n\n";
    for (const auto& s: menu)
        std::cout << s;
    std::cout << "\n";
}

void Add()
{
    while (true)
    {
        std::cout << "Please enter the SID, CID, name and four scores. Enter 0 to finish.\n";
        long long SID;
        std::cin >> SID;
        if (SID == 0) return;
        auto it = std::find_if(allStudents.begin(), allStudents.end(), [SID](const Student &s) { return s.SID == SID; });
        if (it != allStudents.end())
        {
            std::cout << "Duplicated SID.\n";
            std::cin.ignore(100, '\n');
            continue;
        }
        int CID; std::cin >> CID;
        std::string name; std::cin >> name;
        int sC, sM, sE, sP; std::cin >> sC >> sM >> sE >> sP;
        allStudents.emplace_back(SID, name, CID, sC, sM, sE, sP);
    }
}

void Remove()
{
    while (true)
    {
        std::cout << "Please enter SID or name. Enter 0 to finish.\n";
        std::string SIDorName; std::cin >> SIDorName;
        if (SIDorName.size() == 1 && SIDorName[0] == '0')
            return;

        int num = 0;
        if (!std::isupper(SIDorName[0]))
        {
            long long SID = std::stoll(SIDorName);
            auto it = std::find_if(allStudents.begin(), allStudents.end(), [SID](const Student &s) { return s.SID == SID; });
            if (it != allStudents.end())
            {
                allStudents.erase(it);
                num = 1;
            }
        }
        else
        {
            auto size_before = allStudents.size();
            allStudents.remove_if([&SIDorName](const Student &s) { return s.name == SIDorName; });
            num = size_before - allStudents.size();
        }

        std::cout << num << " student(s) removed.\n";
    }
}

void Query()
{
    std::vector<int> total_scores; total_scores.reserve(allStudents.size());
    std::transform(allStudents.begin(), allStudents.end(), std::back_inserter(total_scores), [](const Student &s) { return s.total; });
    std::sort(total_scores.begin(), total_scores.end(), std::greater<int>());

    while (true)
    {
        std::cout << "Please enter SID or name. Enter 0 to finish.\n";
        std::string SIDorName; std::cin >> SIDorName;
        if (SIDorName.size() == 1 && SIDorName[0] == '0')
            return;

        if (!std::isupper(SIDorName[0]))
        {
            long long SID = std::stoll(SIDorName);
            auto it = std::find_if(allStudents.begin(), allStudents.end(), [SID](const Student &s) { return s.SID == SID; });
            if (it != allStudents.end())
            {
                int ranking = std::lower_bound(total_scores.begin(), total_scores.end(), it->total, std::greater<int>()) - 
                    total_scores.begin() + 1;
                std::cout << ranking << " " << std::setw(10) << std::setfill('0') << it->SID << " " << it->CID << " " << it->name << " " << it->scores[score_index::Chinese] << " " << it->scores[score_index::Math] << " " << it->scores[score_index::English] << " " << it->scores[score_index::Prog] << " " << it->total << " " << it->average << "\n";
            }
        }
        else
        {
            for (const auto &s: allStudents)
            {
                if (s.name == SIDorName)
                {
                    int ranking = std::lower_bound(total_scores.begin(), total_scores.end(), s.total, std::greater<int>()) -
                        total_scores.begin() + 1;
                    std::cout << ranking << " " << std::setw(10) << std::setfill('0') << s.SID << " " << s.CID << " " << s.name << " " << s.scores[score_index::Chinese] << " " << s.scores[score_index::Math] << " " << s.scores[score_index::English] << " " << s.scores[score_index::Prog] << " " << s.total << " " << s.average << "\n";
                }
            }
        }
    }
}

void Show_stats()
{
    std::cout << "Please enter class ID, 0 for the whole statistics.\n";
    int cid_query = 0; std::cin >> cid_query;

    struct summary {
        int num_passed = 0;
        int total_score = 0;
    } subj_summaries[score_index::Size];

    int num_total = 0;
    int num_each_subj_passed[score_index::Size + 1] = {0}; // [0] : failed all; [1] : passed 1; [2] : passed 2 ...

    for (const auto &s : allStudents)
    {
        if (cid_query == 0 || s.CID == cid_query)
        {
            ++num_total;
            int num_subj_passed = 0;
            for (auto i = 0; i < 4; ++i)
            {
                subj_summaries[i].total_score += s.scores[i];
                if (s.scores[i] >= 60)
                {
                    ++subj_summaries[i].num_passed;
                    ++num_subj_passed;
                }
            }
            ++num_each_subj_passed[num_subj_passed];
        }
    }

    const char* subject_names[] = {"Chinese", "Mathematics", "English", "Programming"};
    for (auto i = 0; i < 4; ++i)
    {
        std::cout << subject_names[i];

        std::cout << "\nAverage Score: " << static_cast<double>(subj_summaries[i].total_score)/num_total + eps << "\n"
                  << "Number of passed students: " << subj_summaries[i].num_passed << "\n"
                  << "Number of failed students: " << num_total - subj_summaries[i].num_passed << "\n\n";
    }

    std::cout << "Overall:\n"
              << "Number of students who passed all subjects: " << num_each_subj_passed[4] << "\n"
              << "Number of students who passed 3 or more subjects: " << num_each_subj_passed[4] + num_each_subj_passed[3] << "\n"
              << "Number of students who passed 2 or more subjects: " << num_each_subj_passed[4] + num_each_subj_passed[3] + num_each_subj_passed[2] << "\n"
              << "Number of students who passed 1 or more subjects: " << num_each_subj_passed[4] + num_each_subj_passed[3] + num_each_subj_passed[2] + num_each_subj_passed[1] << "\n"
              << "Number of students who failed all subjects: " << num_each_subj_passed[0] << "\n\n";
}

int main()
{
    std::cout << std::fixed << std::setprecision(2);
    while (true)
    {
        display();

        int choice = 0; std::cin >> choice;
        switch (choice)
        {
            case 1:
                Add();
                break;
            case 2:
                Remove();
                break;
            case 3:
                Query();
                break;
            case 4:
                std::cout << "Showing the ranklist hurts students' self-esteem. Don't do that.\n";
                break;
            case 5:
                Show_stats();
                break;
            case 0:
                return 0;
        }
    }
}
