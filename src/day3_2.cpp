#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

char findMatching(std::string p1, std::string p2, std::string p3)
{
    std::vector<char> v1(p1.begin(), p1.end());
    std::vector<char> v2(p2.begin(), p2.end());
    std::vector<char> v3(p3.begin(), p3.end());

    // remove duplicates
    v1.erase( std::unique( v1.begin(), v1.end() ), v1.end() );
    v2.erase( std::unique( v2.begin(), v2.end() ), v2.end() );
    v3.erase( std::unique( v3.begin(), v3.end() ), v3.end() );

    // push in array of charachters
    uint8_t chars1[INT8_MAX] = {0};
    uint8_t chars2[INT8_MAX] = {0};
    uint8_t chars3[INT8_MAX] = {0};

    for(char c1 : v1)
    {
        chars1[c1]++;
    }

    for(char c2 : v2)
    {
        chars2[c2]++;
    }

    for(char c3 : v3)
    {
        chars3[c3]++;
    }

    // find chars which are in both != 0
    for(int i = (int)'A'; i <= (int)'z'; i++)
    {
        if (chars1[i] != 0 && chars2[i] != 0 && chars3[i] != 0)
        {
            // found char
            return (char)i;
        }
    }
        
    return 0;
}

int main()
{
    std::ifstream infile("../input/day3");
    std::string line;
    std::vector<char> res;
    int result = 0;

    int i = 0;
    std::string parts[3];

    while (std::getline(infile, line))
    {
        parts[i%3] = line;
        i++;
        if (i % 3 == 0)
        {
            res.push_back(findMatching(parts[0], parts[1], parts[2]));
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