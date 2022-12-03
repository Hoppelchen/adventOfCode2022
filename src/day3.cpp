#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>



int main()
{
    std::ifstream infile("../input/day3");
    std::string line;
    std::vector<char> res;
    int result = 0;

    while (std::getline(infile, line))
    {
        std::string p1 = line.substr(0, (line.size() / 2));
        std::string p2 = line.substr(line.size() / 2);
        
        std::vector<char> v1(p1.begin(), p1.end());
        std::vector<char> v2(p2.begin(), p2.end());

        // remove duplicates
        v1.erase( std::unique( v1.begin(), v1.end() ), v1.end() );
        v2.erase( std::unique( v2.begin(), v2.end() ), v2.end() );

        // push in array of charachters
        uint8_t chars1[INT8_MAX] = {0};
        uint8_t chars2[INT8_MAX] = {0};

        for(char c1 : v1)
        {
            chars1[c1]++;
        }

        for(char c2 : v2)
        {
            chars2[c2]++;
        }

        // find chars which are in both != 0
        for(int i = (int)'A'; i <= (int)'z'; i++)
        {
            if (chars1[i] != 0 && chars2[i] != 0)
            {
                // found char
                res.push_back((char)i);
                break;
            }
        }
    }

    // calc result;
    for (char r : res)
    {
        if (r >= 'a')
        {
            result += r - 'a' + 1;
        }
        else
        {
            result += r - 'A' + 27;
        }
    }

    std::cout << "result: " <<  result << std::endl;

    return 0;
}