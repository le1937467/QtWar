#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QGraphicsPixmapItem>
#include "card.h"

class CardWidget : public QGraphicsPixmapItem
{
public:
    CardWidget();
    CardWidget(Card *card, bool faceDown = false);
    Card *card;
    bool faceDown;
    void SetCard(Card *card, bool faceDown = false);
};

#endif // CARDWIDGET_H
