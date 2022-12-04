#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <span>


std::pair<int, int> getSections(std::string section)
{
    int start = std::stoi(section.substr(0, section.find('-')));
    int end = std::stoi(section.substr(section.find('-') + 1));

    return std::pair<int,int>(start, end);
}

bool particialContains(std::string line)
{
    std::string p1 = line.substr(0, line.find(','));
    std::string p2 = line.substr(line.find(',') + 1);

    std::pair<int, int> s1 = getSections(p1);
    std::pair<int, int> s2 = getSections(p2);

    return  (s1.first >= s2.first && s1.first <= s2.second) || (s1.second >= s2.first && s1.second <= s2.second)|| (s2.first >= s1.first && s2.first <= s1.second) || (s2.second >= s1.first && s2.second <= s1.second);
}

int main()
{
    std::ifstream infile("../input/day4");
    std::string line;

    int result = 0;

    while (std::getline(infile, line))
    {
        if(particialContains(line))
        {
            result++;
        }
    }

    std::cout << "result: " <<  result << std::endl;

    return 0;
}