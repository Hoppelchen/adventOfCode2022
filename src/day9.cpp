#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>

std::map<std::pair<int,int>,bool> visitedTail;

std::pair<int,int> headPos(0,0);
std::pair<int,int> tailPos(0,0);

int calcVisited()
{
    int res = 0;
    for(const auto& [key, value] : visitedTail)
    {
        if (value == true)
        {
            res++;
        }
    }

    return res;
}

void moveHead(char direction)
{
    switch (direction)
    {
    case 'R':
        headPos.first += 1;
        break;

    case 'L':
        headPos.first -= 1;
        break;

    case 'U':
        headPos.second += 1;
        break;

    case 'D':
        headPos.second -= 1;
        break;
    default:
        break;
    }
}

void calcTail()
{
    if (abs(headPos.first - tailPos.first) >= 2 || abs(headPos.second - tailPos.second) >= 2)
    {
        if (abs(headPos.first - tailPos.first) >= 2)
        {
            // simple to one direction
            if (headPos.first > tailPos.first)
            {
                tailPos.first += 1;
            }
            else
            {
                tailPos.first -= 1;
            }

            if (headPos.second > tailPos.second)
            {
                tailPos.second +=1;
            }
            else if (headPos.second < tailPos.second)
            {
                tailPos.second -=1;
            }
        }
        else if (abs(headPos.second - tailPos.second) >= 2)
        {
            // simple to one direction
            if (headPos.second > tailPos.second)
            {
                tailPos.second += 1;
            }
            else
            {
                tailPos.second -= 1;
            }

            if (headPos.first > tailPos.first)
            {
                tailPos.first +=1;
            }
            else if (headPos.first < tailPos.first)
            {
                tailPos.first -=1;
            }
        }

        visitedTail[tailPos] = true;
    }
}

int main()
{
    std::ifstream infile("../input/day9");
    std::string line;
   
    visitedTail[tailPos] = true;
    while (std::getline(infile, line))
    {
        std::string direction;
        int amount;
        std::stringstream sstream(line);
        sstream >> direction >> amount;
        for (int i = 0; i < amount; i++)
        {
            moveHead(direction[0]);
            calcTail();
        }
    }


    std::cout << "result: " << calcVisited() << std::endl;

    return 0;
}