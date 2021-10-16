#ifndef CARD_H
#define CARD_H

#include <QPixmap>
#include <QString>

enum Suit{
    Clover,
    Diamond,
    Heart,
    Spade
};

class Card
{
public:
    Card(Suit suit, int number, QPixmap pixmap);
    Suit suit;      //Suit of the card
    int number;     //Number of the card, from 1 to 13. 1 being Ace and 13 being King
    QPixmap pixmap; //The Pixmap representing the image and used to draw it on the screen.
};

#endif // CARD_H
