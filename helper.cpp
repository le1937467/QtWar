#include "helper.h"

Helper::Helper()
{
    this->screen = QGuiApplication::primaryScreen();
}

QPointF Helper::getDynamicSize(QSizeF size, float percentX, float percentY)
{
    return QPointF((screen->geometry().width()*percentX/100)-(size.width()/2),
                   (screen->geometry().height()*percentY/100)-(size.height()/2));
}

QScreen* Helper::getScreen()
{
    return this->screen;
}
