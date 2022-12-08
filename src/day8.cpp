#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>

int numRows = 0;
int numColumns = 0;
std::map<std::pair<int,int>,int> map;
std::map<std::pair<int,int>,bool> visible;


int countVisible()
{
    int res = 0;
    for (int  y = 1; y < numRows - 1; y++)
    {
        for (int  x = 1; x < numColumns - 1; x++)
        {
            if(visible[{y,x}] == true)
            {
                res++;
            }
        }
    }

    return res;
}

int countVisibleTrees()
{
    // edges
    int result = 2 * numColumns + 2 * (numRows - 2);

    // make map of visible trees and then count invisble -> just the inner part
    

    // check rows left to right
    for(int y = 1; y < numRows - 1; y++)
    {
        int compare = map[{y, 0}];
        for(int x = 1; x < numColumns - 1; x++)
        {
            if (compare < map[{y, x}])
            {
                visible[{y,x}] = true;
                compare = map[{y, x}];
            }
        }
    }

     // check rows right to left
    for(int y = 1; y < numRows - 1; y++)
    {
        int compare = map[{y, numColumns - 1}];
        for(int x = numColumns - 2; x > 0; x--)
        {
            if (compare < map[{y, x}])
            {
                visible[{y,x}] = true;
                compare = map[{y, x}];
            }
        }
    }

    // check columns top to bottom
    for(int x = 1; x < numColumns - 1; x++)
    {
        int compare = map[{0, x}];
         for(int y = 1; y < numRows - 1; y++)
        {
            if (compare < map[{y, x}])
            {
                visible[{y,x}] = true;
                compare = map[{y, x}];
            }
        }
    }

    // check comuns bottom to top
    for(int x = 1; x < numColumns - 1; x++)
    {
        int compare = map[{numRows - 1, x}];
         for(int y = numRows - 2; y > 0; y--)
        {
            if (compare < map[{y, x}])
            {
                visible[{y,x}] = true;
                compare = map[{y, x}];
            }
        }
    }

    return result + countVisible();
}

int main()
{
    std::ifstream infile("../input/day8");
    std::string line;
    

    while (std::getline(infile, line))
    {
        numColumns = 0;
        for (char c : line)
        {
            // parse rows
            map[{numRows, numColumns}] = c - '0';
            numColumns++;
        }
        numRows++;
    }
    
    std::cout << "result: " << countVisibleTrees() << std::endl;

    return 0;
}