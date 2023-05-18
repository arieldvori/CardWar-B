#pragma once
#include "card.hpp"
#include <vector>
#include <string>


using namespace std;

class Player{
public:
    string name;
    int Winning_count = 0;
    bool isActive = false;
    Card LastTurnCards;
    vector<Card> InHandCards;
    vector<Card> WinningPack;

    Player();//default constructor
    Player(string name);//constructor

    int stacksize();
    int cardesTaken();
};