#ifndef HELPER_H
#define HELPER_H

#include <QPointF>
#include <QSizeF>
#include <QMainWindow>
#include <QGuiApplication>
#include <QScreen>
#include <QTime>

class Helper
{
public:
    Helper();
    QScreen *screen;
    QScreen* getScreen();
    void delay(int time);
    QPointF getDynamicSize(QSizeF size, float percentX, float percentY); // Helper function to get a position by % of screen
};

#endif // HELPER_H
