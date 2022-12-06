#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string_view>

constexpr size_t size = 4;

bool isUnique(std::map<char, uint8_t> &map)
{
    for (const auto &[c, count] : map)
    {
        if (count > 1)
        {
            return false;
        }
    }

    return true;
}

int subroutine(std::string_view data)
{
    std::map<char, uint8_t> map;
    for (int i = 0; i < data.length() - 3; i++)
    {
        map.clear();
        auto sub = data.substr(std::size_t(i), size);

        for (int j = 0; j < size; j++)
        {
            map[sub[j]] = map[sub[j]] + 1; // if not exist, empty element is created
        }

        if (isUnique(map))
        {
            return i + size;
        }
    }

    return -1;
}

int main()
{
    std::ifstream infile("../input/day6");
    std::string line;
    int result = 0;

    while (std::getline(infile, line))
    {
        std::cout << line << std::endl;
        std::cout << "result " << subroutine(line) << std::endl;
    }

    return 0;
}