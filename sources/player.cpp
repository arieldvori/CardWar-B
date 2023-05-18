
#include "player.hpp"
#include <iostream>

Player::Player() {}

Player::Player(std::string name)
{
    this->name = name;
}

int Player::stacksize()
{
    return InHandCards.size();
}

int Player::cardesTaken()
{
    return WinningPack.size();
}