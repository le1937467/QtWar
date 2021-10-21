#include "card.h"

Card::Card(Suit suit, int number, QPixmap pixmap)
{
    this->suit = suit;
    this->number = number;
    this->pixmap = pixmap;
    this->value = number == 1 ? 14 : number;
}
Card::Card(){}      //NOT USED. Default ctor is needed. See CardWidget ctor.

//0 if false, 1 if true, 2 if both are equal
int Card::isBiggerThan(Card *card){
    if(this->value > card->value)
        return 1;
    else if(this->value == card->value)
        return 2;
    else
        return 0;
}
