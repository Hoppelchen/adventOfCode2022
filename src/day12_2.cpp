#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <algorithm>



std::vector<std::string> map;
std::map<std::pair<int, int>, char> distances;

char getValue(std::pair<int, int> coords)
{
    switch (map[coords.first][coords.second])
    {
        case 'S':
            return 'a';
        case 'E':
            return 'z'; 
    }

    return map[coords.first][coords.second];
}

std::vector<std::pair<int, int>> getPossibleNeighbours(std::pair<int, int> pos)
{
    std::vector<std::pair<int,int>> candidates;
    auto y = pos.first;
    auto x = pos.second;
    auto max_y = map.size() - 1;
    auto max_x = map[0].length() - 1;

    if (y > 0)
    {
        candidates.push_back(std::make_pair(y - 1, x));
    }

    if (y < max_y)
    {
        candidates.push_back(std::make_pair(y + 1, x));
    }

    if (x > 0)
    {
        candidates.push_back(std::make_pair(y, x - 1));
    }

    if (x < max_x)
    {
        candidates.push_back(std::make_pair(y, x + 1));
    }

    std::vector<std::pair<int,int>>  filtered;

    std::copy_if(
            candidates.begin(),
            candidates.end(),
            std::back_inserter(filtered),
            [pos](std::pair<int, int> neighbour) -> bool {
                return getValue(neighbour) + 1 >= getValue(pos);
            }
        );

    return filtered;
}

std::map<std::pair<int,int>, int> getDistance(std::pair<int,int> start)
{
    std::vector<std::pair<int,int>> visited;
    std::priority_queue<std::pair<int, std::pair<int,int>>, std::vector<std::pair<int, std::pair<int,int>>>, std::greater<std::pair<int, std::pair<int,int>>>> prioQueue;
    std::map<std::pair<int,int>, int> distances;

    distances[start] = 0;

    prioQueue.push({0, start});
    while (prioQueue.size() > 0)
    {
        std::pair<int, std::pair<int,int>> item = prioQueue.top();
        prioQueue.pop();
        visited.push_back(item.second);

        std::vector<std::pair<int, int>> neighbours = getPossibleNeighbours(item.second);
        for(std::pair<int, int> neighbour : neighbours)
        {
            if ( std::find(visited.begin(), visited.end(), neighbour) != visited.end() )
            {
                // already visited
                continue;
            }

            auto position = distances.find(neighbour);

            if (position == distances.end())
            {
                distances.emplace(neighbour, INT32_MAX);
            }

            int oldDist = distances[neighbour];
            int newDist = distances[item.second] + 1;

            if (newDist < oldDist) {
                distances[neighbour] = newDist;
                prioQueue.push({newDist, neighbour});
            }
        }
    }

    return distances;
}

std::pair<int,int> findChar(char c)
{

    for (uint i = 0; i < map.size(); i++)
    {
        for (uint j = 0; j < map[i].length(); j++)
        {
            if (map[i][j] == c)
            {
                return {i, j};
            }
        }
    }

    return {0,0};
}

int main()
{
    std::ifstream infile("../input/day12");
    std::string line;

    while (std::getline(infile, line))
    {
        map.push_back(line);
    }
 
    std::map<std::pair<int,int>, int> distances = getDistance(findChar('E'));

    int min = INT32_MAX;
    // get all a's
    for (uint i = 0; i < map.size(); i++)
    {
        for (uint j = 0; j < map[i].length(); j++)
        {
            if (map[i][j] == 'a' || map[i][j] == 'S')
            {
                if (distances[{i, j}] < min && distances[{i, j}] != 0)
                {
                    min = distances[{i, j}];
                }
            }
        }
    }
    std::cout << "result " << min << std::endl;

    return 0;
}