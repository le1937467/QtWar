#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QGraphicsPixmapItem>
#include "card.h"
#include <QMouseEvent>
#include <functional>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class CardWidget : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)

public:
    CardWidget();
    CardWidget(Card card);
    CardWidget(Card card, bool faceDown);
    CardWidget(Card *card, bool faceDown = false);
    void SetCard(Card *card, bool faceDown = false);
    void SetCard(Card card, bool faceDown = false);
    void setOnClickEvent(void (*event)());
    Card *card;
    void transitionTo(QPointF dest, bool resize = true, int speed = 500);
private:
    void (*onClickEvent)();
    Card cardOrigin;    //Only used to store the card when it was created by temporary value
    bool faceDown;
    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;
    QParallelAnimationGroup *animGroup;
private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *e);

};

#endif // CARDWIDGET_H
