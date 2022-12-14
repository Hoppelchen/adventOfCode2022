#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

int main()
{
    std::ifstream infile("../input/day1");
    std::string line;
    
    std::vector<int> elves{};
    int cnt = 0;


    while (std::getline(infile, line))
    {
        
        if (line.empty())
        {
            elves.push_back(cnt);
            cnt = 0;
        }   
        else
        {
            std::stringstream  stringstream(line);
            for (int i; stringstream >> i;)
            {
                cnt += i;
            }
        }
    }

    elves.push_back(cnt);

    std::sort(std::begin(elves), std::end(elves), std::greater<int>());
    std::cout << "result: " << (elves[0] + elves[1] + elves[2]) << std::endl;

    return 0;
}