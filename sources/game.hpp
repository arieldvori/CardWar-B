#pragma once
#include "card.hpp"
#include "player.hpp"
#include <vector>
#include <string.h>

namespace ariel{

    class Game{
    public:
        Player& player1;
        Player& player2;
        vector<Card> pack;
        Card Player1LastCard;
        Card Player2LastCard;
        vector<Card> Player1CurrentTurn;
        vector<Card> Player2CurrentTurn;
        Card Draw1Hidden;
        Card Draw2Hidden;
        vector<Card> DrawTempPack;
        vector<Card> LogPack;
        bool isDraw = false;
        bool didPlayer1won = false;
        bool didPlayer2won = false;
        int TurnCount = 0;
        int DrawCount = 0;

        Game(Player& player1, Player& player2);//constructor

        //requested demo functions
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        //empty the draw pack
        void emptyDrawTempPack(vector<Card>& deck);
    };
}