#include <iostream>

#include "Game.h"

int main(int argc, char **argv)
{
    Game game;

    std::cout << "Welcome to Mastermind game!\n There are 6 colours (digits from 1 to 6) which make up the code on four slots.\n"
                 "You have to guess correct digit on correct position! You will receive feedback after each guessing round.\n"
                 "Black pin - X - means that there is a correct digit in correct place. White pin - O - means that there is a correct digit but in wrong place.\n"
                 "You have twelve rounds to guess. Digits can repeat. Good luck! Start typing the sequence!"
              << std::endl;

    return game.run();
}