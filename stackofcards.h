#ifndef STACKOFCARDS_H
#define STACKOFCARDS_H

#include "cardwidget.h"
#include "card.h"
#include "helper.h"
#include <QGraphicsScene>

class StackOfCards
{
private:
    CardWidget *card1;
    CardWidget *card2;
    CardWidget *card3;
public:
    StackOfCards(float x, float y, QGraphicsScene *graphScene, Helper *helper, Card *card);
    ~StackOfCards();
};

#endif // STACKOFCARDS_H