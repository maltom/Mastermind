#include "Game.h"

#include <iostream>
#include <random>
#include <string>
#include <vector>

Game::Game()
{
    m_code.resize(params::codeLength);
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(params::codeSpan.first, params::codeSpan.second);
    for (auto i = 0u; i < params::codeLength; ++i)
    {
        int digit = distribution(generator);
        m_code.at(i) = std::to_string(digit).at(0);
    }
#ifdef TEST
    std::cout << "SECRET CODE: " << m_code << std::endl;
#endif
}

std::string Game::checkAnswer(const std::string &answer)
{
    std::vector<bool> matchedCode(params::codeLength, false);
    std::vector<bool> matchedAnswer(params::codeLength, false);

    int exactMatches{0};
    for (auto i = 0u; i < params::codeLength; ++i)
    {
        if (answer.at(i) == m_code.at(i))
        {
            ++exactMatches;
            matchedCode.at(i) = true;
            matchedAnswer.at(i) = true;
        }
    }

    int nearMatches{0};
    for (auto i = 0u; i < params::codeLength; ++i)
    {
        for (auto j = 0u; j < params::codeLength; ++j)
        {
            if (answer.at(i) == m_code.at(j) && !matchedAnswer.at(i) && !matchedCode.at(j))
            {
                ++nearMatches;
                matchedCode.at(j) = true;
                matchedAnswer.at(i) = true;
                break;
            }
        }
    }

    std::string result;
    result.append(exactMatches, pins::black);
    result.append(nearMatches, pins::white);

    return result;
}

bool Game::isGameWon(const std::string &answer)
{
    if (answer.size() != params::codeLength)
    {
        return false;
    }

    for (const auto &in : answer)
    {
        if (in != pins::black)
        {
            return false;
        }
    }
    return true;
}

int Game::run()
{
    for (auto i = 0u; i < params::rounds; ++i)
    {
        std::string answer;
        std::cin >> answer;

        auto isInputValid = [&answer]
        {
            if (answer.size() != params::codeLength)
                return false;

            for (auto &in : answer)
            {
                if (in < '1' || in > '6')
                    return false;
            }
            return true;
        };

        if (!isInputValid())
        {
            std::cout << "Wrong input provided! Type it once more:" << std::endl;
            --i;
            continue;
        }

        auto result = checkAnswer(answer);
        auto isWon = isGameWon(result);
        if (isWon)
        {
            std::cout << "Congratulations! You won in round #" << i + 1 << "!" << std::endl;
            return 0;
        }
        else
        {
            std::string filler(params::codeLength - result.size(), pins::filler);
            std::cout << "Code comparison result: " << result << filler << " Rounds left: " << params::rounds - (i + 1) << std::endl;
        }
    }
    std::cout << "Oh no, you lost!\nThe secret code was: " << m_code << std::endl;
    return 0;
}