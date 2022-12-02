#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

enum class RPS : int {
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3
};

// winning overview
std::map<RPS, RPS> lookup = {{RPS::ROCK, RPS::SCISSORS}, {RPS::SCISSORS, RPS::PAPER}, {RPS::PAPER, RPS::ROCK}};

int main()
{
    std::ifstream infile("../input/day2");
    std::string line;
    int result = 0;

    while (std::getline(infile, line))
    {
        RPS opponent = RPS(line[0] - 'A' + 1);
        RPS me = RPS(line[2] - 'X' + 1);

        if (me == opponent)
        {
            // draw
            result += 3;
        }
        else if (lookup[me] == opponent)
        {
            // winning
            result += 6;
        }

        // add choosen value to result
        result += static_cast<int>(me);
    }

    std::cout << "result: " <<  result << std::endl;

    return 0;
}