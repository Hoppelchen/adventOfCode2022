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

enum class RESULT : int {
    LOSE = 1,
    DRAW = 2,
    WIN = 3
};

// which rps needed to be choosen (enemy -> the result = what I choose)
std::map<std::pair<RPS, RESULT>, RPS> lookup = {
    {std::make_pair(RPS::ROCK,RESULT::LOSE), RPS::SCISSORS}, 
    {std::make_pair(RPS::ROCK,RESULT::DRAW), RPS::ROCK}, 
    {std::make_pair(RPS::ROCK,RESULT::WIN), RPS::PAPER}, 
    {std::make_pair(RPS::PAPER,RESULT::LOSE), RPS::ROCK}, 
    {std::make_pair(RPS::PAPER,RESULT::DRAW), RPS::PAPER},
    {std::make_pair(RPS::PAPER,RESULT::WIN), RPS::SCISSORS},
    {std::make_pair(RPS::SCISSORS,RESULT::LOSE), RPS::PAPER},
    {std::make_pair(RPS::SCISSORS,RESULT::DRAW), RPS::SCISSORS},
    {std::make_pair(RPS::SCISSORS,RESULT::WIN), RPS::ROCK}
};

int main()
{
    std::ifstream infile("../input/day2");
    std::string line;
    int result = 0;

    while (std::getline(infile, line))
    {
        RPS opponent = RPS(line[0] - 'A' + 1);
        RESULT res = RESULT(line[2] - 'X' + 1);
        RPS me = lookup[std::make_pair(opponent, res)];

        if (res == RESULT::DRAW)
        {
            result += 3;
        }
        else if (res == RESULT::WIN)
        {
            result += 6;
        }

        result += static_cast<int>(me);
    }

    std::cout << "result: " <<  result << std::endl;

    return 0;
}