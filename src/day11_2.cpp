#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

class Monkey;

std::vector<Monkey> monkeys;
int count = 0;
int globalDivisor = 1;

class Monkey
{
public:
    int number;
    std::vector<uint64_t> items;
    std::string operation[3];
    uint64_t divisible;
    int onTrue;
    int onFalse;
    uint64_t inspected = 0;

    Monkey(std::vector<std::string> input)
    {
        number = count++;
        // starting items
        std::string line = input[1];
        line = line.substr(line.find(':') + 2);
        
        size_t pos = 0;
        std::string token;
        while ((pos = line.find(',')) != std::string::npos) {
            token = line.substr(0, pos);
            items.push_back(stoi(token));
            line.erase(0, pos + 2);
        }

        items.push_back(stoi(line));

        // operation
        line = input[2];
        int i = 0;
        line = line.substr(line.find('=') + 2);

        while ((pos = line.find(' ')) != std::string::npos) {
            token = line.substr(0, pos);
            operation[i] = token;
            line.erase(0, pos + 1);
            i++;
        }

        operation[i] = line;


        divisible = stoi(input[3].substr(input[3].find_last_of(' ') + 1));
       
        globalDivisor *= divisible;
        
        onTrue = stoi(input[4].substr(input[4].find_last_of(' ') + 1));
        onFalse = stoi(input[5].substr(input[5].find_last_of(' ') + 1));

    }

    void print()
    {
        std::cout << "-- monkey  " << number << " --" << std::endl;
        for (int a : this->items)
        {
            std::cout << a << " ";
        }
        
        std::cout << std::endl;

        std::cout << "ops " << std::endl;
        for (std::string a : this->operation)
        {
            std::cout << a << std::endl;
        }

        std::cout << "div " << divisible << std::endl;
        std::cout << "true " << onTrue << std::endl;
        std::cout << "false " << onFalse << std::endl;
    }

    void doStep()
    {
        int size = items.size();
        for (int i = 0; i < size; i++)
        {
            uint64_t item = items[i];
            inspected++;

            uint64_t res = 0;
            if (operation[0] == "old")
            {
                res = item;
            }
            if (operation[1] == "*")
            {
                if (operation[2] == "old")
                {
                    res *= res;
                }
                else
                {
                    res *= stoi(operation[2]);
                }
            }
            else if (operation[1] == "+")
            {
                if (operation[2] == "old")
                {
                    res += res;
                }
                else
                {
                    res += stoi(operation[2]);
                }
            }

            bool check = res % divisible == 0;

            // reducde item so value isnt getting big
            if (res >= globalDivisor)
            {
                res = res - ((res / globalDivisor) * globalDivisor);
            }

            if (check)
            {
                
                monkeys[onTrue].items.push_back(res);
            }
            else
            {
                
                monkeys[onFalse].items.push_back(res);
            }
        }

        items = std::vector<uint64_t>();
    }
};

void print()
{
    for (Monkey& a: monkeys)
    {
        a.print();
    }
}

void doStep()
{
    for (Monkey&  a: monkeys)
    {
        a.doStep();
    }
}


int main()
{
    std::ifstream infile("../input/day11");
    std::string line;
    std::vector<std::string> data;

    while (std::getline(infile, line))
    {

        if (!line.empty())
        {
            data.push_back(line);
        }
        else
        {
            monkeys.push_back({data});
            data = std::vector<std::string>();
        }
    }

    monkeys.push_back({data});

    //print();
    for (int i = 0; i < 10000; i++)
    {
        doStep();
    }

    std::vector<uint64_t> result;
    for (Monkey& m: monkeys)
    {
        result.push_back(m.inspected);
    }

    std::sort(result.begin(), result.end(), std::greater<int>());

    std::cout << "result: " << (result[0] * result[1])  << std::endl;

    return 0;
}