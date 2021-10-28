#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QGraphicsPixmapItem>
#include "card.h"
#include <QMouseEvent>
#include <functional>

class CardWidget : public QGraphicsPixmapItem
{
public:
    CardWidget();
    CardWidget(Card card);
    CardWidget(Card card, bool faceDown);
    CardWidget(Card *card, bool faceDown = false);
    void SetCard(Card *card, bool faceDown = false);
    void SetCard(Card card, bool faceDown = false);
    void setOnClickEvent(void (*event)());
private:
    void (*onClickEvent)();
    Card cardOrigin;    //Only used to store the card when it was created by temporary value
    Card *card;
    bool faceDown;
private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
};

#endif // CARDWIDGET_H
