#include "cardwidget.h"

CardWidget::CardWidget()
{
    CardWidget(nullptr); //In case we need to do extra setups, we do them all in the same function
}

CardWidget::CardWidget(Card card)   //Constructor that supports creating by value instead of reference
{
    this->cardOrigin = card;
    this->card = &cardOrigin;
    CardWidget(this->card);
}

CardWidget::CardWidget(Card *card, bool faceDown)
{
    if(card != nullptr){
        this->SetCard(card, faceDown);
    }
}

void CardWidget::SetCard(Card *card, bool faceDown)
{
    this->card = card;
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
