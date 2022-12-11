#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

int step = 0;
int X = 1;
int result = 0;
std::vector<int> steps{40, 80, 120, 160, 200, 240};

std::map<std::pair<int, int>, char> CRT = {};
int line = 0;

void print()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            std::cout << CRT[{i,j}];
        }
        std::cout << std::endl;
    }
}

void drawSprit()
{
    if ((step % 40) == (X - 1) || (step % 40) == (X) || (step % 40) == (X + 1))
    {
        CRT[{line, step%40}] = 'X';
    }
    
}

void increaseStep()
{
    drawSprit();
    step++;
    if(std::find(steps.begin(), steps.end(), step) != steps.end()) 
    {
        line++;
    }
}

int main()
{
    std::ifstream infile("../input/day10");
    std::string line;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            CRT[{i, j}] = '.';
        }
    }


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

    print();

    return 0;
}