#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "card.h"
#include <QDirIterator>
#include <QPalette>
#include <QLayout>
#include "cardwidget.h"
#include <QGraphicsAnchorLayout>
#include <QGraphicsWidget>
#include "helper.h"
#include <QTextDocument>
#include <QTextCharFormat>
#include <QPen>
#include <QPushButton>
#include <QHash>
#include <QTextCursor>
#include "stackofcards.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum GameState{
    PreDeal,
    Start,
    GameOver,
    GameWon
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QList<Card*> allCards;
    Helper *helper;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *graphScene;
    QGraphicsView *graphView;
    QPushButton *dealButton;
    QTextCharFormat format;
    QPen outlinePen;
    QTextDocument *youDoc;
    QTextDocument *compDoc;
    QHash<QString, StackOfCards*> stacks; //String is used to reference to where the card is for easier deletion.
    void CreateFaceDownStackOfCards(float x, float y, QString ref);  //Creates a stack of card at position x,y in PERCENTAGES
    void LoadCards();
    void SetupUI();
    void ChangeState(GameState gameState);
};
#endif // MAINWINDOW_H
