#ifndef HELPER_H
#define HELPER_H

#include <QPointF>
#include <QSizeF>
#include <QMainWindow>

class Helper
{
private:
    QMainWindow *mw;
public:
    Helper(QMainWindow *mw);
    QPointF getDynamicSize(QSizeF size, float percentX, float percentY); // Helper function to get a position by % of screen
};

#endif // HELPER_H
