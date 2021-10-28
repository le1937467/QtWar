#include "mainwindow.h"

#include <QApplication>
#include "scrolleater.h"

int main(int argc, char *argv[])
{
    ScrollEater *scrollEater = new ScrollEater();
    QApplication a(argc, argv);
    a.installEventFilter(scrollEater);
    MainWindow w(&a);
    w.show();
    return a.exec();
}
