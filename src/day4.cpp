#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>


std::string getSections(std::string section)
{
    std::string result = "";
    int start = std::stoi(section.substr(0, section.find('-')));
    int end = std::stoi(section.substr(section.find('-') + 1));

    for (int i = start; i <= end; i++)
    {
        result += i + '0';
    }

    return result;
}

bool fullyContains(std::string line)
{
    std::string p1 = line.substr(0, line.find(','));
    std::string p2 = line.substr(line.find(',') + 1);

    std::string s1 = getSections(p1);
    std::string s2 = getSections(p2);
    

    return (s1.find(s2) != std::string::npos || s2.find(s1) != std::string::npos);
}

int main()
{
    std::ifstream infile("../input/day4");
    std::string line;

    int result = 0;

    while (std::getline(infile, line))
    {
        if(fullyContains(line))
        {
            result++;
        }
    }

    std::cout << "result: " <<  result << std::endl;

    return 0;
}