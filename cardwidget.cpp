#include "cardwidget.h"

CardWidget::CardWidget()
{
    CardWidget(nullptr); //In case we need to do extra setups, we do them all in the same function
}

CardWidget::CardWidget(Card *card, bool faceDown)
{
    if(card != nullptr){
        this->SetCard(card, faceDown);
    }

}

void CardWidget::SetCard(Card *card, bool faceDown){
    this->card = card;
    if(!faceDown)
        setPixmap(this->card->pixmap);
    else
        setPixmap(QPixmap(":/img/Images/Cards/back.png"));
}
