#include "card.hpp"
#include <iostream>
#include <string.h>
#include <string>


Card::Card(){
    //do nothing
}

Card::Card( Type type, Num num)
{
    type = type;
    num = num;
}

void Card::toString()
{
    string s_type;
    string s_num;

    switch (this->type) {
        case hearts:
            s_type = "hearts";
            break;
        case spaders:
            s_type = "spaders";
            break;
        case clubs:
            s_type = "clubs";
            break;
        case diamonds:
            s_type = "diamonds";
            break;
        
    }

    switch (this->num)
    {
        case two:
            s_num = "two";
            break;
        case three:
            s_num = "three";
            break;
        case four:
            s_num = "four";
            break;
        case five:
            s_num = "five";
            break;
        case six:
            s_num = "six";
            break;
        case seven:
            s_num = "seven";
            break;
        case eight:
            s_num = "eight";
            break;
        case nine:
            s_num = "nine";
            break;
        case ten:
            s_num = "ten";
            break;
        case jack:
            s_num = "jack";
            break;
        case queen:
            s_num = "queen";
            break;
        case king:
            s_num = "king";
            break;
        case ace:
            s_num = "ace";
            break;
    }

    // Prints te card details
    std::cout << s_num << " of " << s_type << endl;
}