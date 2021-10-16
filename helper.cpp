#include "helper.h"

Helper::Helper(QMainWindow *mw)
{
    this->mw = mw;
}

QPointF Helper::getDynamicSize(QSizeF size, float percentX, float percentY){
    return QPointF((mw->width()*percentX/100)-(size.width()/2),(mw->height()*percentY/100)-(size.height()/2));
}
