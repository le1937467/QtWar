#ifndef SCROLLEATER_H
#define SCROLLEATER_H

#include <QObject>
#include <QEvent>
#include <QDebug>

class ScrollEater : public QObject
{
    Q_OBJECT
public:
    explicit ScrollEater(QObject *parent = nullptr);
protected:
  bool eventFilter(QObject *obj, QEvent *event) override;
signals:

};

#endif // SCROLLEATER_H
