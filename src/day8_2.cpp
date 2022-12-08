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
std::map<std::pair<int,int>,int> view;


int getMax()
{
    return std::max_element
    (
        std::begin(view), std::end(view),
        [] (const auto & view1, const auto & view2) {
            return view1.second < view2.second;
        }
    )->second;
}


int calcView(int y, int x)
{
    int res = 0;
    // to left
    int mult = 0;
    for (int i = x - 1; i >= 0; i--)
    {
        mult++;
        if (map[{y,i}] >= map[{y,x}])
        {
            break;
        }
    }

    res = mult;
    mult = 0;
    for (int i = x + 1; i < numColumns; i++)
    {
        mult++;
        if (map[{y,i}] >= map[{y,x}])
        {
           break;
        }
    }
    res *= mult;

    mult = 0;
    
    for (int i = y - 1; i >= 0; i--)
    {
        mult++;
        if (map[{i,x}] >= map[{y,x}])
        {
            break;
        }
    }
    res *= mult;

    mult = 0;
    for (int i = y + 1; i < numRows; i++)
    {
        mult++;
        if (map[{i,x}] >= map[{y,x}])
        {
            break;
        }
    }
    res *= mult;

    return res;
}

void calcView()
{
    for (int  y = 1; y < numRows - 1; y++)
    {
        for (int  x = 1; x < numColumns - 1; x++)
        {
            if (visible[{y,x}] == true)
            {
                view[{y,x}] = calcView(y,x);
            }
            
        }
    }
}

void calcCovered()
{
    // edges
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

    calcCovered();
    calcView();

    std::cout << "result: " << getMax() << std::endl;

    return 0;
}