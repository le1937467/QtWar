#include "card.h"

Card::Card(Suit suit, int number, QPixmap pixmap)
{
    this->suit = suit;
    this->number = number;
    this->pixmap = pixmap;
}
