#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>

std::vector<std::vector<char>> stacks;

void print()
{
    std::cout << "-------" << std::endl;
    for (std::vector<char> stack : stacks)
    {
        for (char element : stack)
        {
            std::cout << element;
        }
        std::cout << std::endl;
        std::cout << "-------" << std::endl;

    }
}

int main()
{
    std::ifstream infile("../input/day5");
    std::string line;

    bool modeCommands = false;
    while (std::getline(infile, line))
    {
        if (stacks.size() == 0)
        {
            stacks = std::vector<std::vector<char>>((line.size() / 4 + 1));
        }

        if (line.size() < 1)
        {
            continue;
        }

        int size = line.size();
        int idx = 0;
        
        if (modeCommands == true)
        {
            std::stringstream sstream(line);
            std::string delimiter[3];
            int count;
            int from;
            int to;
            sstream >> delimiter[0] >> count >> delimiter[1] >> from >> delimiter[2] >> to;

            for (int i = 0; i < count; i++)
            {
                char tmp = stacks[from - 1].back();
                stacks[from - 1].pop_back();
                stacks[to - 1].push_back(tmp);
            }
        }
        else
        {
            while(size > 0)
            {
                std::string sub = line.substr(0, 3);

                if (sub[1] >= '0' && sub[1] <= '9')
                {
                    modeCommands = true;
                    break;
                }

                if (sub[1] != ' ')
                {
                    stacks[idx].insert(stacks[idx].begin(), sub[1]);
                }

                if (size >= 4)
                {
                    line = line.substr(4);
                }
                
                size -= 4;
                idx++;
            }
        }

    }

    print();
    std::string result = "";
    for (std::vector<char> stack : stacks)
    {
        result += stack.back();
    }

    std::cout << "result: " <<  result << std::endl;

    return 0;
}