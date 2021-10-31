#include "cardwidget.h"

CardWidget::CardWidget()
{
    this->onClickEvent = nullptr;
    CardWidget(nullptr); //In case we need to do extra setups, we do them all in the same function
}

CardWidget::CardWidget(Card card)   //Constructor that supports creating by value instead of reference
{
    this->cardOrigin = card;
    this->card = &cardOrigin;
    CardWidget(this->card);
}

CardWidget::CardWidget(Card card, bool faceDown)   //Constructor that supports creating by value instead of reference
{
    this->cardOrigin = card;
    this->card = &cardOrigin;
    CardWidget(this->card, faceDown);
}

CardWidget::CardWidget(Card *card, bool faceDown)
{
    this->onClickEvent = nullptr;
    if(card != nullptr){
        this->SetCard(card, faceDown);
    }
}

void CardWidget::SetCard(Card *card, bool faceDown)
{
    if(card != nullptr){
        this->card = card;
        if(!faceDown)
            setPixmap(this->card->pixmap);
        else
            setPixmap(QPixmap(":/img/Images/Cards/back.png"));
    }
    else{
        setPixmap(QPixmap());
    }
}

void CardWidget::SetCard(Card card, bool faceDown)
{
    this->card = new Card(card);
    if(!faceDown)
        setPixmap(this->card->pixmap);
    else
        setPixmap(QPixmap(":/img/Images/Cards/back.png"));
}


void CardWidget::setOnClickEvent(void (*event)())
{
    this->onClickEvent = *event;

}

void CardWidget::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    if(this->onClickEvent != nullptr){
        onClickEvent();
    }
}

void CardWidget::transitionTo(QPointF dest, bool resize, int speed){
    if(resize)
        this->setScale(0.10);
    animGroup = new QParallelAnimationGroup();
    animation1 = new QPropertyAnimation(this, "pos");
    animation2 = new QPropertyAnimation(this, "scale");

    animation1->setEndValue(dest);
    animation2->setEndValue(1.00);
    animation1->setDuration(speed);
    animation2->setDuration(speed);


    animGroup->addAnimation(animation1);
    animGroup->addAnimation(animation2);
    animGroup->start();

}
