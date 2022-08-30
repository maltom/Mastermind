#pragma once
#include <string>
#include <utility>

namespace params
{
    constexpr int rounds{12};
    constexpr int codeLength{4};
    constexpr std::pair<int, int> codeSpan{1, 6};
}

namespace pins
{
    constexpr char black{'X'};
    constexpr char white{'O'};
    constexpr char filler{'-'};
}

class Game
{
private:
    std::string checkAnswer(const std::string &answer);
    bool isGameWon(const std::string &answer);
    std::string m_code;

public:
    Game();
    int run();
};