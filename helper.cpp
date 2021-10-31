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
void Helper::delay(int time){
    QTime dieTime= QTime::currentTime().addMSecs(time);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QScreen* Helper::getScreen()
{
    return this->screen;
}
