#include "stackofcards.h"

StackOfCards::StackOfCards(float x, float y, QGraphicsScene *graphScene, Helper *helper, Card *card)
{
    card1 = new CardWidget(card, true);
    card1->setPos(helper->getDynamicSize(card1->boundingRect().size(), x, y));
    graphScene->addItem(card1);
    card2 = new CardWidget(card, true);
    card2->setPos(helper->getDynamicSize(card1->boundingRect().size(), x-0.5, y-0.5));
    graphScene->addItem(card2);
    card3 = new CardWidget(card, true);
    card3->setPos(helper->getDynamicSize(card1->boundingRect().size(), x-1, y-1));
    graphScene->addItem(card3);
}

StackOfCards::~StackOfCards()
{
    delete card1;
    delete card2;
    delete card3;
}
