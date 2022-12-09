#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>

constexpr int numKnots = 10;

std::map<std::pair<int,int>,bool> visitedTail;

std::vector<std::pair<int,int>> knots(numKnots);

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
        knots[0].first += 1;
        break;

    case 'L':
        knots[0].first -= 1;
        break;

    case 'U':
        knots[0].second += 1;
        break;

    case 'D':
        knots[0].second -= 1;
        break;
    default:
        break;
    }
}

void calcTail(std::pair<int, int> &headPos, std::pair<int, int>&tailPos)
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
    }
}

int main()
{
    std::ifstream infile("../input/day9");
    std::string line;
   
    visitedTail[knots[numKnots - 1]] = true;
    while (std::getline(infile, line))
    {
        std::string direction;
        int amount;
        std::stringstream sstream(line);
        sstream >> direction >> amount;
        for (int i = 0; i < amount; i++)
        {
            moveHead(direction[0]);
            for (int i = 1; i < numKnots; i++)
            {
                calcTail(knots[i - 1], knots[i]);
            }
            visitedTail[knots[numKnots - 1]] = true;
        }
    }


    std::cout << "result: " << calcVisited() << std::endl;

    return 0;
}