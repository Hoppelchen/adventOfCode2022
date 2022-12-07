#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <sstream>
#include <algorithm>

class F
{
public:
    std::string name;
    size_t size;
    F(std::string line)
    {
        std::stringstream sstream(line);
        sstream >> size >> name;
    }
};

class D
{
public:
    std::string name;
    std::map<std::string, std::shared_ptr<D>> dirs = {};
    std::map<std::string, std::shared_ptr<F>>files = {};
    D(std::string line)
    {
        name = line.substr(4);
    }

    D(std::string line, std::shared_ptr<D> parent)
    {
        name = line.substr(4);
        dirs[".."] = parent;
    }
};

int getDirectorySize(std::shared_ptr<D> d)
{
    int sum = 0;
    for (const auto& [key, value] : d->files) {
        sum += value->size;
    }

    for (const auto& [key, value] : d->dirs) {
        if (key != "..")
        {
            sum += getDirectorySize(value);
        }    
    }

    return sum;
}


std::vector<std::shared_ptr<D>> dirs;

int main()
{
    std::ifstream infile("../input/day7");
    std::string line;
    
    dirs.push_back(std::make_shared<D>("dir /"));
    std::shared_ptr<D> currentDir = dirs[0];

    while (std::getline(infile, line))
    {
        if (line.compare("$ cd /") == 0)
        {
            continue;
        }

        if (line[0] == '$')
        {
            // command
            if(line.rfind("$ cd", 0) == 0)
            {
                std::string dir = line.substr(5);
                currentDir = currentDir->dirs[dir];
            }  
        }
        else if (line[0] >= '0' && line[0] <= '9')
        {
            std::shared_ptr<F> f = std::make_shared<F>(line);
            currentDir->files[f->name] = f;
        }
        else
        {
            std::shared_ptr<D> d = std::make_shared<D>(line, currentDir);
            currentDir->dirs[d->name] = d;
            dirs.push_back(d);
        }
       
    }

    int target = 100000;
    int32_t result;
    for (std::shared_ptr<D> it : dirs)
    {
        int size = getDirectorySize(it);
        if (size < target)
        {
            result += size;
        }
    }

    std::cout << result << std::endl;

    return 0;
}