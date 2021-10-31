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
    CardWidget *animCard1;
    CardWidget *animCard2;
    QGraphicsScene *scene;
    Helper *helper;
public:
    CardWidget *card3;
    StackOfCards(float x, float y, QGraphicsScene *graphScene, Helper *helper, Card *card);
    void setOnClickEvent(void (*event)());
    void transitionTo(QPointF dest1, QPointF dest2, bool resize = true, int speed = 500);
    ~StackOfCards();
};

#endif // STACKOFCARDS_H
