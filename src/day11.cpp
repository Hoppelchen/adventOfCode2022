#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

class Monkey;

std::vector<Monkey> monkeys;
int count = 0;

class Monkey
{
public:
    int number;
    std::vector<int> items;
    std::string operation[3];
    int divisible;
    int onTrue;
    int onFalse;
    int inspected = 0;

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
        onTrue = stoi(input[4].substr(input[4].find_last_of(' ') + 1));
        onFalse = stoi(input[5].substr(input[5].find_last_of(' ') + 1));

    }

    void print()
    {
        std::cout << "-- monkey  " << this->number << " --" << std::endl;
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
            int item = items[i];
            inspected++;

            int res = 0;
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

            res /= 3;
            if (res % divisible == 0)
            {
                monkeys[onTrue].items.push_back(res);
            }
            else
            {
                monkeys[onFalse].items.push_back(res);
            }
        }

        items = std::vector<int>();
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
    for (int i = 0; i < 20; i++)
    {
        doStep();
    }

    std::vector<int> result;
    for (Monkey& m: monkeys)
    {
        result.push_back(m.inspected);
    }

    std::sort(result.begin(), result.end(), std::greater<int>());

    std::cout << "result: " << (result[0] * result[1])  << std::endl;

    return 0;
}