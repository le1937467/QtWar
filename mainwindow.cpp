#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    helper = new Helper(this);
    LoadCards();
    SetupUI();

    //Singleton
    if(!instance)
        instance = this;
    else{
        delete instance;
        instance = this;
    }
}

//Makes this a singleton to be available to onClick static methods
MainWindow* MainWindow::getInstance()
{
    if(instance)
        return instance;
    else{
        throw new QException(); //Error, instance not found
    }
}

void MainWindow::SetupUI()
{
    //Setup the green background and start maximized
    this->setStyleSheet("background: url(:/img/Images/bg.jfif)");
    this->showMaximized();

    //Setup drawing area
    graphView = ui->graphicsView;
    graphScene = new QGraphicsScene;
    graphScene->setSceneRect(0,0,width(), height());
    graphView->setScene(graphScene);

    //Set base interface that won't change


    //Base objects needed for formatting
    format.setFont(QFont("times", 30));
    outlinePen = QPen(QColor(255,255,255), 1.3, Qt::SolidLine);
    format.setTextOutline(outlinePen);

    //You Text.
    QGraphicsTextItem *youText = new QGraphicsTextItem;
    youDoc = new QTextDocument;
    QTextCursor youCursor = QTextCursor(youDoc);
    youCursor.insertText("You", format);
    youText->setDocument(youDoc);
    youText->setPos(helper->getDynamicSize(youText->boundingRect().size(), 42, 100));
    graphScene->addItem(youText);

    //Computer Text.
    QGraphicsTextItem *compText = new QGraphicsTextItem;
    compDoc = new QTextDocument;
    QTextCursor compCursor = QTextCursor(compDoc);
    compCursor.insertText("Computer", format);
    compText->setDocument(compDoc);
    compText->setPos(helper->getDynamicSize(compText->boundingRect().size(), 58, 0));
    graphScene->addItem(compText);


    //Setup pre-deal screen
    ChangeState(GameState::PreDeal);

}

void MainWindow::CreateFaceDownStackOfCards(float x, float y, QString ref){
    stacks[ref] = new StackOfCards(x, y, graphScene,helper,allCards[0]);
}

void MainWindow::DealCards(){
    QList<Card*> copyOfAllCards = allCards;
    int halfLen = allCards.size()/2; //26
    ShuffleDeck(&copyOfAllCards);
    myCards = allCards.mid(0, halfLen);
    compCards = allCards.mid(halfLen);
}

void MainWindow::ShuffleDeck(QList<Card*> *deck){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck->begin(), deck->end(), g);
}

Card MainWindow::PopCardFromDeck(QList<Card*> deck){
    Card card = *deck[0];
    deck.remove(0);
    return card;
}

void MainWindow::DeckClick(){

    MainWindow *mw = MainWindow::getInstance(); //Get instance from static context
    Card myCard = mw->PopCardFromDeck(mw->myCards);
    Card compCard = mw->PopCardFromDeck(mw->compCards);
    mw->myCardWidget = new CardWidget(myCard);
    mw->myCardWidget->setPos(mw->helper->getDynamicSize(mw->myCardWidget->boundingRect().size(), 50, 40));
    mw->compCardWidget = new CardWidget(compCard);
    mw->compCardWidget->setPos(mw->helper->getDynamicSize(mw->compCardWidget->boundingRect().size(), 50, 60));
    mw->graphScene->addItem(mw->myCardWidget);
    mw->graphScene->addItem(mw->compCardWidget);

}

void MainWindow::ChangeState(GameState gameState){
    switch(gameState){
    case GameState::PreDeal:
        CreateFaceDownStackOfCards(40,50, "deal_stack");
        dealButton = new QPushButton("Deal");
        dealButton->setFont(QFont("times", 18));
        dealButton->setGeometry(0,0, 150,50);   //Need to reset x,y. Then resize. Then move.
        dealButton->move(helper->getDynamicSize(dealButton->size(), 60, 50).toPoint());
        connect(dealButton, &QPushButton::clicked, [this](){
            ChangeState(GameState::Start);
        });
        graphScene->addWidget(dealButton);

        break;
    case GameState::Start:
        dealButton->setVisible(false);
        delete stacks["deal_stack"];
        //Creating the stacks of cards
        CreateFaceDownStackOfCards(22,0, "computer_cards");
        CreateFaceDownStackOfCards(33,82, "your_cards");

        // Sets the DeckClick() static function to execute when clicking on the stack of cards
        stacks["your_cards"]->setOnClickEvent(&MainWindow::DeckClick);

        //Dealing and shuffling the cards
        DealCards();

        break;
    case GameState::GameOver:

        break;
    case GameState::GameWon:

        break;
    }
}


void MainWindow::LoadCards()
{
    QString cardsFolder = QDir::currentPath().left(QDir::currentPath().lastIndexOf("/")) + "/QtWar/Images/Cards";

    //Load Clover Cards
    QDirIterator *it = new QDirIterator(cardsFolder + "/Clover", QStringList() << "*.png");
    while (it->hasNext()){
        allCards.append(new Card(Suit::Clover, it->fileName().split("_")[1].toInt(), QPixmap(it->next())));
    }

    //Load Diamond Cards
    it = new QDirIterator(cardsFolder + "/Diamond", QStringList() << "*.png");
    while (it->hasNext()){
        allCards.append(new Card(Suit::Diamond, it->fileName().split("_")[1].toInt(), QPixmap(it->next())));
    }

    //Load Heart Cards
    it = new QDirIterator(cardsFolder + "/Heart", QStringList() << "*.png");
    while (it->hasNext()){
        allCards.append(new Card(Suit::Heart, it->fileName().split("_")[1].toInt(), QPixmap(it->next())));
    }

    //Load Spade Cards
    it = new QDirIterator(cardsFolder + "/Spade", QStringList() << "*.png");
    while (it->hasNext()){
        allCards.append(new Card(Suit::Spade, it->fileName().split("_")[1].toInt(), QPixmap(it->next())));
    }

    qDebug()<<"Cards loaded:" << allCards.size() << "cards.";
}

MainWindow::~MainWindow()
{
    delete ui;
}

