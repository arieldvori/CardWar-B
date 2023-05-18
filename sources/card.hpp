#pragma once
#include <string>

using namespace std;

enum Type {hearts, spaders, clubs, diamonds}; 
enum Num {two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};

class Card{
public:
    Type type;
    Num num;

    Card();//default constructor 
    Card(Type shape, Num num);//constructor
    void toString();//prints the card type and num

};