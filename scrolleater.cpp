#include "scrolleater.h"

ScrollEater::ScrollEater(QObject *parent) : QObject(parent)
{

}
bool ScrollEater::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::Wheel)
  {
    return true;
  }
  else
  {
    return QObject::eventFilter(obj, event);
  }
}
