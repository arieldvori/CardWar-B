#include "game.hpp"
#include "card.hpp"
#include "player.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace ariel;
using namespace std;

Game::Game(Player &player1, Player &player2)
    : player1(player1), player2(player2){

    //checks if the game is starting with non active players
    if(player1.isActive == true){
        throw invalid_argument(player1.name + "is in another game");
    }
    if(player2.isActive == true){
        throw invalid_argument(player2.name + "is in another game");
    }

    //after game has started, make the players as active.
    player1.isActive = true;
    player2.isActive = true;

    // create new pack of 52 cards and push into vector
    Card card;
    vector<Card> deck;
    for(int shape = 0; shape < 4; shape++){
        for(int num = 0; num < 13; num++){
            card.type = Type(shape);
            card.num = Num(num);
            deck.push_back(card);
        }
    }
    //random seed
    srand(time(NULL));
    // shuffle the deck
    while(!deck.empty()){
        //choosing random index and than push it to the back of the deck
        size_t rand_index = (unsigned long)rand() % deck.size();
        pack.push_back(deck[rand_index]);
        deck.erase(deck.begin() + (int)rand_index);
    }

    // giving 26 card to each player.
    for(int i = 0; i < 26; i++){
        player1.InHandCards.push_back(pack[0]);
        pack.erase(pack.begin());
        player2.InHandCards.push_back(pack[0]);
        pack.erase(pack.begin());
    }
}

void ariel::Game::playTurn(){
    //throw if the turn is between the same player
    if(&player1 == &player2){
        throw invalid_argument("You have to choose two diffrent players");
    }
    //if there is still cards in the players hands
    if(player1.InHandCards.size()){
        //if there is a winner, give him all the winning cards
        if(!isDraw){
            TurnCount++;
            while(Player1CurrentTurn.size()){
                Player1CurrentTurn.erase(Player1CurrentTurn.begin());
                Player2CurrentTurn.erase(Player2CurrentTurn.begin());
            }
        }

        //starting the turn, each player draw one card from the beggining of rhe pack in his hands
        Player1LastCard = player1.InHandCards[0];
        player1.InHandCards.erase(player1.InHandCards.begin());
        Player2LastCard = player2.InHandCards[0];
        player2.InHandCards.erase(player2.InHandCards.begin());

        //insert every card to the log
        LogPack.push_back(Player1LastCard);
        LogPack.push_back(Player2LastCard);

        //if player 1 won
        if((Player1LastCard.num > Player2LastCard.num)){
            didPlayer1won = true;
            didPlayer2won = false;
            player1.Winning_count++;

            //if this win was in the middle of draw.
            if(isDraw){
                emptyDrawTempPack(player1.WinningPack);
                isDraw = false;
            }
            //inserting the card 2 last card to the winner 
            player1.WinningPack.push_back(Player1LastCard);
            player1.WinningPack.push_back(Player2LastCard);
            Player1CurrentTurn.push_back(Player1LastCard);
            Player2CurrentTurn.push_back(Player2LastCard);
        }

        //if player 2 won
        else if((Player1LastCard.num < Player2LastCard.num)){
            didPlayer1won = false;
            didPlayer2won = true;
            player2.Winning_count++;

            //if this win was in the middle of draw.
            if(isDraw){
                emptyDrawTempPack(player2.WinningPack);
                isDraw = false;
            }
            //inserting the card 2 last card to the winner 
            player2.WinningPack.push_back(Player1LastCard);
            player2.WinningPack.push_back(Player2LastCard);
            Player1CurrentTurn.push_back(Player1LastCard);
            Player2CurrentTurn.push_back(Player2LastCard);
        }

        //if draw
        else if(Player1LastCard.num == Player2LastCard.num){
            didPlayer1won = false;
            didPlayer2won = false;
            isDraw = true;
            DrawCount++;
            //insert the last card of each player to their current turn vector
            Player1CurrentTurn.push_back(Player1LastCard);
            Player2CurrentTurn.push_back(Player2LastCard);
            //if there is still cards in their hands
            if(player1.InHandCards.size()){
                Draw1Hidden = player1.InHandCards[0];
                player1.InHandCards.erase(player1.InHandCards.begin());
                Draw2Hidden = player2.InHandCards[0];
                player2.InHandCards.erase(player2.InHandCards.begin());

                //inserting the visible and the hidden cards to the drawtemp vector
                DrawTempPack.push_back(Player1LastCard);
                DrawTempPack.push_back(Player2LastCard);
                DrawTempPack.push_back(Draw1Hidden);
                DrawTempPack.push_back(Draw2Hidden);
                playTurn();
            }
            //if they are out of cards
            else{
                //if the draw pack is empty
                if(!DrawTempPack.size()){
                    player1.WinningPack.push_back(Player1LastCard);
                    player2.WinningPack.push_back(Player2LastCard);
                }
                while (DrawTempPack.size()){
                    //split the draw cards cack to the 2 players
                    player1.WinningPack.push_back(DrawTempPack[0]);
                    DrawTempPack.erase(DrawTempPack.begin());
                    player2.WinningPack.push_back(DrawTempPack[0]);
                    DrawTempPack.erase(DrawTempPack.begin());
                }
                isDraw = false;
            }
        }
    }
    else{
        throw invalid_argument("No more cards");
    }
}

void ariel::Game::emptyDrawTempPack(vector<Card> &winner_deck){
    //empty the draw pack to the winner deck
    for(Card card : DrawTempPack){
        winner_deck.push_back(DrawTempPack[0]);
        DrawTempPack.erase(DrawTempPack.begin());
    }
}

void ariel::Game::printLastTurn(){
    //while there is still card in the current turn vector
    while(Player2CurrentTurn.size()){
        cout << player1.name << " played with ";
        Player1CurrentTurn[0].toString();
        cout << "and" << player2.name << " played with ";
        Player2CurrentTurn[0].toString();

        //if draw
        if(Player1CurrentTurn[0].num == Player2CurrentTurn[0].num){
            cout << "Draw " << endl;
        }
        //remove for printing the other cards
        Player1CurrentTurn.erase(Player1CurrentTurn.begin());
        Player2CurrentTurn.erase(Player2CurrentTurn.begin());
    }
    if(didPlayer1won){
        cout << player1.name << " have won." << endl;
    }
    else if(didPlayer2won){
        cout << player2.name << " have won." << endl;
    }
}

void ariel::Game::playAll(){
    while (player1.InHandCards.size()){
        playTurn();
    }
}
void ariel::Game::printWiner(){
    if(player1.WinningPack.size() > player2.WinningPack.size()){
        cout << player1.name << " have won." << endl;
    }
    else if(player1.WinningPack.size() < player2.WinningPack.size()){
        cout << player2.name << "have won." << endl;
    }
    else if(player1.WinningPack.size() == player2.WinningPack.size()){
        cout << "Draw." << endl;
    }
}
void ariel::Game::printLog(){    
    cout << "the number of turns is : " << TurnCount << endl;
    bool draw = false;

    Card Player1card;
    Card Player2card;

    for(int i = 1; i <= TurnCount; i++){
        //if it is not in the middle of a draw
        if(!draw){
            cout << "Turn " << i << ": " << endl;
        }

        Player1card = LogPack[0];
        Player2card = LogPack[1];

        cout << player1.name << " has played with: ";
        Player1card.toString();
        cout << player2.name << " has played with: ";
        Player2card.toString();
        if(Player1card.num > Player2card.num){
            draw = false;
            cout << player1.name << " won this turn." << endl;
            //delete the used card from the log
            LogPack.erase(LogPack.begin());
            LogPack.erase(LogPack.begin());
        }
        else if(Player1card.num < Player2card.num){
            draw = false;
            cout << player2.name << " won this turn." << endl;
            //delete the used card from the log
            LogPack.erase(LogPack.begin());
            LogPack.erase(LogPack.begin());
        }
        //if the next 2 cards are draw
        while(LogPack.size() && (LogPack[0].num == LogPack[1].num)){
            //if it is not in the middle of a draw
            if(!draw){
                i++;
                cout << "Turn " << i << ": " << endl;
                cout << player1.name << " has played with: ";
                LogPack[0].toString();
                cout << player2.name << " has played with: ";
                LogPack[1].toString();
            }
            cout << "Draw." << endl;
            LogPack.erase(LogPack.begin());
            LogPack.erase(LogPack.begin());

            //if we are in the middle od a draw
            if(draw){
                cout << player1.name << " has played with: ";
                LogPack[0].toString();
                cout << player2.name << " has played with: ";
                LogPack[1].toString();
            }
            draw = true;
            //if it is draw we doesnt need to i++ it is concidered in the same turn
            i--;
        }
    }
}
void ariel::Game::printStats(){
    cout << player1.name << " Won rate: " << (double)player1.Winning_count / (double)TurnCount << endl;
    cout << player2.name << " Won rate: " << (double)player2.Winning_count / (double)TurnCount << endl;
    cout << "The cards which " << player1.name << " has won: " << endl;
    for(Card card : player1.WinningPack){
        card.toString();
    }
    cout << "The cards which " << player2.name << " has won: " << endl;
    for (Card card : player2.WinningPack)
    {
        card.toString();
    }
    cout << "The rate of draw: " << (double)DrawCount / (double)TurnCount << endl;
}