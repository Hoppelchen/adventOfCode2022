#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

int step = 0;
int X = 1;
int result = 0;
std::vector<int> steps{20, 60, 100, 140, 180, 220};

void increaseStep()
{
    // TODO check X on step
    step++;
    if(std::find(steps.begin(), steps.end(), step) != steps.end()) 
    {
        result += (step * X);
    }
}

int main()
{
    std::ifstream infile("../input/day10");
    std::string line;
  
    while (std::getline(infile, line))
    {
        if (line == "noop")
        {
            increaseStep();
        }
        else
        {
            std::string command;
            int amount;
            std::stringstream sstream(line);
            sstream >> command >> amount;

            if (command == "addx")
            {
                increaseStep();
                increaseStep();
                X += amount;
            }
        }
    }

    std::cout << "result: " << result << std::endl;

    return 0;
}