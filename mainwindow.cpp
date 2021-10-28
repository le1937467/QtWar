#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *app, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->app = app;
    helper = new Helper();
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

    //Set screen size
    QSize size = helper->getScreen()->availableSize();
    size.setWidth(size.width()-8);
    this->setFixedSize(size);
    this->setGeometry(helper->getScreen()->geometry());


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
    youText->setPos(helper->getDynamicSize(youText->boundingRect().size(), 42, 83));
    graphScene->addItem(youText);

    //Computer Text.
    QGraphicsTextItem *compText = new QGraphicsTextItem;
    compDoc = new QTextDocument;
    QTextCursor compCursor = QTextCursor(compDoc);
    compCursor.insertText("Computer", format);
    compText->setDocument(compDoc);
    compText->setPos(helper->getDynamicSize(compText->boundingRect().size(), 58, 10));
    graphScene->addItem(compText);

    //My won cards pile
    myWonCardsWidget = new CardWidget(allCards[0]);
    myWonCardsWidget->setPos(helper->getDynamicSize(myWonCardsWidget->boundingRect().size(), 85, 83));
    myWonCardsWidget->SetCard(nullptr);
    graphScene->addItem(myWonCardsWidget);

    //Computer's won cards pile
    compWonCardsWidget = new CardWidget(allCards[0]);
    compWonCardsWidget->setPos(helper->getDynamicSize(compWonCardsWidget->boundingRect().size(), 85, 10));
    compWonCardsWidget->SetCard(nullptr);
    graphScene->addItem(compWonCardsWidget);

    //Your score Text.
    youScoreText = new QGraphicsTextItem;
    myScoreDoc = new QTextDocument;
    yourScoreCursor = new QTextCursor(myScoreDoc);
    yourScoreCursor->insertText("+0", format);
    youScoreText->setDocument(myScoreDoc);
    youScoreText->setPos(helper->getDynamicSize(youScoreText->boundingRect().size(), 90, 83));
    graphScene->addItem(youScoreText);
    youScoreText->setVisible(false);


    //Computer score Text.
    compScoreText = new QGraphicsTextItem;
    compScoreDoc = new QTextDocument;
    compScoreCursor = new QTextCursor(compScoreDoc);
    compScoreCursor->insertText("+0", format);
    compScoreText->setDocument(compScoreDoc);
    compScoreText->setPos(helper->getDynamicSize(compScoreText->boundingRect().size(), 90, 10));
    graphScene->addItem(compScoreText);
    compScoreText->setVisible(false);

    //WAR Text.
    warText = new QGraphicsTextItem;
    warDoc = new QTextDocument;
    warCursor = new QTextCursor(warDoc);
    warCursor->insertText("WAR: +0", format);
    warText->setDocument(warDoc);
    warText->setPos(helper->getDynamicSize(warText->boundingRect().size(), 90, 50));
    graphScene->addItem(warText);
    warText->setVisible(false);

    //Cards Left Text.
    cardLeftText = new QGraphicsTextItem;
    cardLeftDoc = new QTextDocument;
    cardLeftCursor = new QTextCursor(cardLeftDoc);
    cardLeftCursor->insertText("Cards left: 0", format);
    cardLeftText->setDocument(cardLeftDoc);
    cardLeftText->setPos(helper->getDynamicSize(cardLeftText->boundingRect().size(), 10, 45));
    graphScene->addItem(cardLeftText);
    cardLeftText->setVisible(false);

    //Cards in the middle
    myCardWidget = new CardWidget(allCards[0]); //Init with card for proper placement using size
    myCardWidget->setPos(helper->getDynamicSize(myCardWidget->boundingRect().size(), 45, 45));
    myCardWidget->SetCard(nullptr);             //Reset the card since it was only for size
    compCardWidget = new CardWidget(allCards[0]);
    compCardWidget->setPos(helper->getDynamicSize(compCardWidget->boundingRect().size(), 55, 45));
    compCardWidget->SetCard(nullptr);
    graphScene->addItem(myCardWidget);
    graphScene->addItem(compCardWidget);


    //Setup pre-deal screen
    ChangeState(GameState::PreDeal);

}

void MainWindow::UpdateScore()
{
    if(myScore > 0 && !youScoreText->isVisible())
        youScoreText->setVisible(true);
    if(compScore > 0 && !compScoreText->isVisible())
        compScoreText->setVisible(true);

    myScoreDoc->undo();
    yourScoreCursor->insertText("+"+QString::number(myScore), format);
    compScoreDoc->undo();
    compScoreCursor->insertText("+"+QString::number(compScore), format);
    warDoc->undo();
    warCursor->insertText("WAR: +"+QString::number(warScore), format);
    cardLeftDoc->undo();
    cardLeftCursor->insertText("Cards Left: "+QString::number(myCards.size()), format);

    if(endGame){
        if(myScore > compScore){
            ChangeState(GameState::GameWon);
        }
        else{
            ChangeState(GameState::GameOver);
        }
    }
}

void MainWindow::CreateFaceDownStackOfCards(float x, float y, QString ref){
    stacks[ref] = new StackOfCards(x, y, graphScene,helper,allCards[0]);
}

void MainWindow::DealCards(){
    QList<Card*> copyOfAllCards = allCards;
    int halfLen = allCards.size()/2; //26
    ShuffleDeck(&copyOfAllCards);
    myCards = copyOfAllCards.mid(0, halfLen);
    compCards = copyOfAllCards.mid(halfLen);
}

void MainWindow::ShuffleDeck(QList<Card*> *deck){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck->begin(), deck->end(), g);
}

void MainWindow::SetValues(){
    canClickDeck = true;
    myScore = 0;
    compScore = 0;
    warScore = 0;
    isInWar = false;
    endGame = false;
}

Card MainWindow::PopCardFromDeck(QList<Card*> *deck){
    Card card = Card(*deck->at(0));
    deck->remove(0);
    if(deck->size() <= 0)
        endGame = true;
    return card;
}

void MainWindow::DeckClick()
{
    MainWindow *mw = MainWindow::getInstance(); //Get instance from static context
    if(mw->canClickDeck){

        /*
         *   -----------Put the cards on the table------------------
         */
        mw->canClickDeck = false;
        mw->myCard = mw->PopCardFromDeck(&mw->myCards);
        mw->compCard = mw->PopCardFromDeck(&mw->compCards);
        mw->myCardWidget->SetCard(mw->myCard);
        mw->compCardWidget->SetCard(mw->compCard);


        /*
         *   --------Wait a bit and pick the round's winner---------
         */
        mw->app->processEvents();   //VERY IMPORTANT - Otherwise, UI freezes before changes are processed
        QThread::sleep(1);          //1s sleep


        int doesPlayerWin = mw->myCard.isBiggerThan(&mw->compCard);

        if(doesPlayerWin == 0)
        {
            //COMPUTER WINS ROUND
            if(!mw->isInWar){
                mw->compScore += 2;
                mw->compWonCardsWidget->SetCard(mw->compCard);
            }
            else{
                mw->compScore += mw->warScore+2;
                mw->compWonCardsWidget->SetCard(mw->compCard);
                mw->warText->setVisible(false);
                mw->isInWar = false;
            }
        }
        else if(doesPlayerWin == 1)
        {
            //PLAYER WINS ROUND
            if(!mw->isInWar){
                mw->myScore += 2;
                mw->myWonCardsWidget->SetCard(mw->myCard);
            }
            else{
                mw->myScore += mw->warScore+2;
                mw->myWonCardsWidget->SetCard(mw->myCard);
                mw->warText->setVisible(false);
                mw->isInWar = false;
            }
        }
        else
        {
            //NOBODY WINS ROUND -> START WAR
            if(!mw->isInWar){
                mw->warText->setVisible(true);
                mw->isInWar = true;
                mw->warScore = 2;
            }
            else{
                mw->warScore += 2;
            }
        }

        mw->myCardWidget->SetCard(nullptr);     //Reset the pixmaps
        mw->compCardWidget->SetCard(nullptr);

        mw->UpdateScore();  //Update the score
        mw->canClickDeck = true;


    }

}

void MainWindow::ChangeState(GameState gameState){
    switch(gameState){
    case GameState::PreDeal:
        SetValues();
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
        cardLeftText->setVisible(true);
        dealButton->setVisible(false);
        delete stacks["deal_stack"];
        //Creating the stacks of cards
        CreateFaceDownStackOfCards(45,10, "computer_cards");
        CreateFaceDownStackOfCards(55,83, "your_cards");

        // Sets the DeckClick() static function to execute when clicking on the stack of cards
        stacks["your_cards"]->setOnClickEvent(&MainWindow::DeckClick);

        //Dealing and shuffling the cards
        DealCards();

        UpdateScore();

        break;
    case GameState::GameOver:
        delete stacks["computer_cards"];
        delete stacks["your_cards"];

        myWonCardsWidget->SetCard(nullptr);
        compWonCardsWidget->SetCard(nullptr);
        cardLeftText->setVisible(false);
        warText->setVisible(false);
        youScoreText->setVisible(false);
        compScoreText->setVisible(false);

        gameEndText = new QGraphicsTextItem;
        gameEndDoc = new QTextDocument;
        gameEndCursor = new QTextCursor(gameEndDoc);
        gameEndCursor->insertText("YOU LOST :(", format);
        gameEndText->setDocument(gameEndDoc);
        gameEndText->setPos(helper->getDynamicSize(gameEndText->boundingRect().size(), 50, 50));
        graphScene->addItem(gameEndText);

        app->processEvents();
        QThread::sleep(3);
        gameEndText->setVisible(false);
        ChangeState(GameState::PreDeal);

        break;
    case GameState::GameWon:

        delete stacks["computer_cards"];
        delete stacks["your_cards"];

        myWonCardsWidget->SetCard(nullptr);
        compWonCardsWidget->SetCard(nullptr);
        cardLeftText->setVisible(false);
        warText->setVisible(false);
        youScoreText->setVisible(false);
        compScoreText->setVisible(false);

        gameEndText = new QGraphicsTextItem;
        gameEndDoc = new QTextDocument;
        gameEndCursor = new QTextCursor(gameEndDoc);
        gameEndCursor->insertText("YOU WON :)", format);
        gameEndText->setDocument(gameEndDoc);
        gameEndText->setPos(helper->getDynamicSize(gameEndText->boundingRect().size(), 50, 50));
        graphScene->addItem(gameEndText);

        app->processEvents();
        QThread::sleep(3);
        gameEndText->setVisible(false);
        ChangeState(GameState::PreDeal);

        break;
    }
}


void MainWindow::LoadCards()
{
    QString cardsFolder = QDir::currentPath() + "/Images/Cards";

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

