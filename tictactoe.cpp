#include "tictactoe.h"
#include "ui_tictactoe.h"
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QTimer>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include <QSplashScreen>

QString win = "";
int animTime = 0;
int winComp = 0;

TicTacToe::TicTacToe(int lg,int s, int k, QWidget *parent)
    : QMainWindow(parent)
{
    //setting setting gui to the TicTacToe widget
    setupUi(this);
    paint = 0; //which background to be painted
    set = s; //which animation set is selected
    key = k; //which key is used for which user
    play1Num = 0; //player 1 score in number tic tac toe
    play2Num = 0; //player 2 score in number tic tac toe
    matchPlayed = 0; //total match playerd
    play1Win = 0; //total player 1 win matches
    play2Win = 0; //total player 2 win mathces
    matchDraw = 0; //total match drawn
    playWith = 0; //which options is selected from with friend and with computer
    langInd = lg; // setting language index of game

    //setting language for game
    langList << ":/media/rd_square/Important/Qt projects/TicTacToe/translations/tictactoe_en_us.qm"
            << ":/media/rd_square/Important/Qt projects/TicTacToe/translations/tictactoe_hi.qm";

    //hiding useless contents
    enterLabel->hide();
    play1Label->hide();
    play2Label->hide();
    p1Edit->hide();
    p2Edit->hide();
    playButton->hide();
    winLabel->hide();
    backButton->hide();

    //starting animation of TicTacToe label
    animate = new QMovie(":/media/rd_square/Important/Qt projects/TicTacToe/Images/animation.gif");
    animationLabel->setMovie(animate);
    animate->setScaledSize(animationLabel->size());
    animate->start();

    //setting connections of the buttons
    connect(quitButton, SIGNAL(clicked(bool)),
            this, SLOT(quitPressed()));
    connect(pcButton, SIGNAL(clicked(bool)),
            this, SLOT(pcPressed()));
    connect(pfButton, SIGNAL(clicked(bool)),
            this, SLOT(pfPressed()));
    connect(settingButton, SIGNAL(clicked(bool)),
            this, SLOT(settingPressed()));
    connect(playButton, SIGNAL(clicked(bool)),
            this, SLOT(playPressed()));
    connect(adButton, SIGNAL(clicked(bool)),
            this, SLOT(adPressed()));
    connect(atButton, SIGNAL(clicked(bool)),
            this, SLOT(atPressed()));
    connect(backButton, SIGNAL(clicked(bool)),
            this, SLOT(backPressed()));

    //disabling all the button and generating welcome message
    pfButton->setEnabled(false);
    pcButton->setEnabled(false);
    settingButton->setEnabled(false);
    atButton->setEnabled(false);
    adButton->setEnabled(false);
    quitButton->setEnabled(false);
    welcome = new QMovie(":/media/rd_square/Important/Qt projects/TicTacToe/Images/wtAnim.gif");
    wLabel->setMovie(welcome);
    welcome->setScaledSize(wLabel->size());

    //setting timer to on and off welcome message
    QTimer::singleShot(1000, this, SLOT(welcomeMessage()));
    QTimer::singleShot(4000,this, SLOT(endWelcomeMessage()));
}

void TicTacToe::adPressed()
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    devolper = new Developer(this);
    connect(devolper, SIGNAL(okAccepted()),
           this, SLOT(deleteDev()));
    devolper->exec();
}

void TicTacToe::atPressed(){
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    about = new About(this);
    connect(about, SIGNAL(okAccepted()),
            this, SLOT(deleteAbout()));
    about->exec();
}

void TicTacToe::deleteAbout()
{
    about->accept();
    about->hide();
    delete about;
}

void TicTacToe::deleteDev()
{
    devolper->accept();
    devolper->hide();
    delete devolper;
}

void TicTacToe::playPressed()
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    p2Edit->setEnabled(true);
    play1Name = p1Edit->text();
    play2Name = p2Edit->text();
    if (play1Name.isEmpty()) {
        play1Name = "Player_1";
    }
    if (play2Name.isEmpty()) {
        play2Name = "Player_2";
    }

    //hiding some widgets
    enterLabel->hide();
    play1Label->hide();
    play2Label->hide();
    p1Edit->hide();
    p2Edit->hide();
    playButton->hide();
    backButton->hide();

    //do some random calculation
    qsrand(time(0)); //initializing random seed
    currTurn = qrand() % 10000; //generating random numbers
    QString tempName;
    if (currTurn > 5000) {
        currTurn = 0;
        tempName = play1Name;
    } else {
        currTurn = 1;
        tempName = play2Name;
    }

    QString fStr, sStr;
    if (key==0) {
        fStr = tr("Right-Mouse-Key");
        sStr = tr("Left-Mouse-Key");
    } else {
        sStr = tr("Right-Mouse-Key");
        fStr = tr("Left-Mouse-Key");
    }

    scoreBoard = new ScoreBoard(play1Name, play2Name,play1Win, play2Win, this);
    scoreBoard->setGeometry(20,90,220,265);

    if (playWith == 0) {
        board = new Board(play1Name,play2Name,set, key, currTurn,langInd, this);
        connect(board, SIGNAL(turnChanged(int)),
                scoreBoard, SLOT(changeTurn(int)));
        connect(board, SIGNAL(matchFinished(int)),
                this, SLOT(gameFinished(int)));

        board->setGeometry(270,90,300,300);

        paint = 1;
        repaint();
        scoreBoard->show();
        board->show();
        scoreBoard->changeTurn(currTurn);

        QMessageBox::information(this, tr("Some Tips! - %1").arg(qApp->applicationName()),
                                 tr("<qt>1. <i><font color=\"red\">%1</font></i> will use <i><font color=\"blue\">%2</font></i> to play his/her turn."
                                    "<hr></br>2. <i><font color=\"red\">%3</font></i> will use <i><font color=\"blue\">%4</font></i> to play his/her turn.</qt>").arg(play1Name).arg(fStr).arg(play2Name).arg(sStr),
                                 QMessageBox::Ok | QMessageBox::Default);
    } else {
        aiBoard = new AiBoard(play1Name, play2Name, set, key, currTurn,langInd, this);
        connect(aiBoard, SIGNAL(turnChanged(int)),
                scoreBoard, SLOT(changeTurn(int)));
        connect(aiBoard, SIGNAL(matchFinished(int)),
                this, SLOT(gameFinished(int)));

        aiBoard->setGeometry(270,90,300,300);

        paint = 1;
        repaint();
        scoreBoard->show();
        aiBoard->show();
        scoreBoard->changeTurn(currTurn);

        QMessageBox::information(this, tr("Some Tips! - %1").arg(qApp->applicationName()),
                                 tr("<qt>Use %1 to play the game.").arg(fStr),
                                 QMessageBox::Ok | QMessageBox::Default);
    }
    QMessageBox::information(this, tr("First Turn! - %1").arg(qApp->applicationName()),
                             tr("<qt><font size=\"6\" color=\"green\">%1's turn first.").arg(tempName),
                             QMessageBox::Ok | QMessageBox::Default);
}

void TicTacToe::gameFinished(int player)
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    matchPlayed++;
    if (player == -1) {
        matchDraw++;
        //do some random calculation
        qsrand(time(0)); //initializing random seed
        currTurn = qrand() % 10000; //generating random numbers
        if (currTurn > 5000) {
            currTurn = 0;
        } else {
            currTurn = 1;
        }
    } else if (player == 0) {
        win = play1Name;
        play1Win++;
        currTurn = 0;
    } else if (player == 1) {
        win = play2Name;
        play2Win++;
        currTurn = 1;
        winComp = 1;
    }
    QTimer::singleShot(1000, this, SLOT(gameWin()));
    finalBoard = new FinalBoard(play1Name, play2Name,matchPlayed ,play1Win, play2Win, this);
    finalBoard->setGeometry(90,90,480, 190);
    connect(finalBoard, SIGNAL(goToHome()),
            this, SLOT(homePressed()));
    connect(finalBoard, SIGNAL(quitGame()),
            this, SLOT(quitPressed()));
    connect(finalBoard, SIGNAL(replayGame()),
            this, SLOT(replayGame()));
}

void TicTacToe::gameWin()
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    //deleting board and scoreBoard
    if(playWith == 0) {
        board->hide();
        delete board;
    }else {
        aiBoard->hide();
        delete aiBoard;
    }
    scoreBoard->hide();
    delete scoreBoard;
    paint = 2;
    repaint();
    winLabel->show();
    if (win.isEmpty()){
        winLabel->setText(tr("Regrets!\nMatch is draw by both player."));
        winLabel->setStyleSheet("QLabel { color: red }");
    } else {
        winLabel->setStyleSheet("QLabel { color: green }");
        winLabel->setText(tr("Congratulations!\n%1 have won this match.").arg(win));
    }
    if (winComp == 1 && playWith == 1) {
        winLabel->setStyleSheet("QLabel { color: red }");
        winLabel->setText(tr("You Lose!\nSquare have won this match."));
    }
    winning = new QLabel(this);
    winning->setGeometry(130, 100, 410, 330);
    welcome = new QMovie(":/media/rd_square/Important/Qt projects/TicTacToe/Images/winning.gif");
    winning->setMovie(welcome);
    welcome->setScaledSize(winning->size());
    if (!win.isEmpty() && ((winComp==0) || (winComp==1 && playWith==0))) {
        winning->show();
        animTime = 2000;
    }
    winComp = 0;

    QTimer::singleShot(animTime, this, SLOT(stopWinningAnimation()));
    welcome->start();
    win = "";
    play1Num = 0;
    play2Num = 0;
}

void TicTacToe::stopWinningAnimation()
{
    winning->hide();
    animTime = 0;
    finalBoard->show();
    quitButton->hide();
}

void TicTacToe::homePressed()
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    adButton->setGeometry(atButton->geometry());
    atButton->setGeometry(x,y,180,40);
    winning->setPixmap(QPixmap());
    delete finalBoard;
    delete welcome;
    delete winning;
    paint = 0;
    repaint();
    winLabel->hide();
    pfButton->show();
    pcButton->show();
    settingButton->show();
    adButton->show();
    atButton->show();
    quitButton->show();
    matchPlayed = 0;
    play1Win = 0;
    play2Win = 0;
}

void TicTacToe::replayGame()
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    winning->setPixmap(QPixmap());
    delete finalBoard;
    delete welcome;
    delete winning;
    scoreBoard = new ScoreBoard(play1Name, play2Name,play1Win, play2Win, this);

    if (playWith == 0) {
        board = new Board(play1Name,play2Name,set, key, currTurn,langInd, this);
        connect(board, SIGNAL(turnChanged(int)),
                scoreBoard, SLOT(changeTurn(int)));
        connect(board, SIGNAL(matchFinished(int)),
                this, SLOT(gameFinished(int)));
        scoreBoard->setGeometry(20,90,220,265);
        board->setGeometry(270,90,300,300);

        paint = 1;
        repaint();
        scoreBoard->show();
        board->show();
        scoreBoard->changeTurn(currTurn);
        quitButton->show();
        winLabel->hide();
        QString tempName;
        if (currTurn == 0) {
            tempName = play1Name;
        } else {
            tempName = play2Name;
        }
        QMessageBox::information(this, tr("First Turn! - %1").arg(qApp->applicationName()),
                                 tr("<qt><font size=\"6\" color=\"green\">%1's turn first.").arg(tempName),
                                 QMessageBox::Ok | QMessageBox::Default);
    } else {
        aiBoard = new AiBoard(play1Name,play2Name,set, key, currTurn,langInd, this);
        connect(aiBoard, SIGNAL(turnChanged(int)),
                scoreBoard, SLOT(changeTurn(int)));
        connect(aiBoard, SIGNAL(matchFinished(int)),
                this, SLOT(gameFinished(int)));
        scoreBoard->setGeometry(20,90,220,265);
        aiBoard->setGeometry(270,90,300,300);

        paint = 1;
        repaint();
        scoreBoard->show();
        aiBoard->show();
        scoreBoard->changeTurn(currTurn);
        quitButton->show();
        winLabel->hide();
        QString tempName;
        if (currTurn == 0) {
            tempName = play1Name;
        } else {
            tempName = play2Name;
        }
        QMessageBox::information(this, tr("First Turn! - %1").arg(qApp->applicationName()),
                                 tr("<qt><font size=\"6\" color=\"green\">%1's turn first.").arg(tempName),
                                 QMessageBox::Ok | QMessageBox::Default);
    }
}

void TicTacToe::settingReceived(int ind1, int ind2, int ind3, int langc)
{
    set = ind1;
    key = ind2;
    langInd = ind3;
    setting->accept();
    delete setting;

    if (langc == 0) {
        int tempCount = ++count;
        this->hide();
        if(tempCount%2 == 0) {
            QSplashScreen *splash = new QSplashScreen;
            splash->setPixmap(QPixmap(":/media/rd_square/Important/Qt projects/TicTacToe/Images/tacLogo.png").scaled(250,250, Qt::IgnoreAspectRatio));
            splash->show();

            Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;

            splash->showMessage(QObject::tr("Opening Tic-Tac-Toe..."), topRight, Qt::white);

            //setting translator
            QTranslator ltra;
            ltra.load(langList.at(ind3));
            qApp->installTranslator(&ltra);

            splash->showMessage(QObject::tr("Lading game modules..."), topRight, Qt::white);
            TicTacToe *newGame = new TicTacToe(ind3,ind1,ind2);
            newGame->count = tempCount;

            newGame->show();
            splash->finish(newGame);
            delete splash;
            delete this;
        } else {
            QSplashScreen *splash = new QSplashScreen;
            splash->setPixmap(QPixmap(":/media/rd_square/Important/Qt projects/TicTacToe/Images/tacLogo.png").scaled(250,250, Qt::IgnoreAspectRatio));
            splash->show();

            Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;

            splash->showMessage(QObject::tr("Opening Tic-Tac-Toe..."), topRight, Qt::white);

            //setting translator
            QTranslator ltra;
            ltra.load(langList.at(ind3));
            qApp->installTranslator(&ltra);

            splash->showMessage(QObject::tr("Lading game modules..."), topRight, Qt::white);
            TicTacToe *newGame1 = new TicTacToe(ind3,ind1,ind2);
            newGame1->count = tempCount;

            newGame1->show();
            splash->finish(newGame1);
            delete splash;
            delete this;
        }
    }

}

void TicTacToe::settingPressed()
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    setting = new Setting(set, key, langInd, this);
    connect(setting, SIGNAL(settingDone(int,int, int, int)),
            this, SLOT(settingReceived(int,int, int, int)));
    setting->exec();
}

void TicTacToe::pfPressed()
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    playWith = 0;
    //hiding other buttons and main panel
    settingButton->hide();
    pfButton->hide();
    pcButton->hide();

    //placing butons at different positions
    x = atButton->geometry().left();
    y = atButton->geometry().top();
    atButton->setGeometry(adButton->geometry());
    adButton->setGeometry(200,430,180,40);

    //Show enter display to enter player's name
    enterLabel->show();
    play1Label->show();
    play1Label->setText(tr("Player_1: "));
    play2Label->setText(tr("Player_2: "));
    play2Label->show();
    p2Edit->setText(tr("Player_2"));
    p1Edit->show();
    p2Edit->show();
    playButton->show();
    backButton->show();
}

void TicTacToe::backPressed()
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    enterLabel->hide();
    play1Label->hide();
    play2Label->hide();
    p1Edit->hide();
    p2Edit->setEnabled(true);
    p2Edit->hide();
    playButton->hide();
    backButton->hide();
    paint = 0;
    repaint();
    settingButton->show();
    pfButton->show();
    pcButton->show();
    adButton->setGeometry(atButton->geometry());
    atButton->setGeometry(x,y,180,40);
}

void TicTacToe::pcPressed()
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    playWith = 1;
    //hiding other buttons and main panel
    settingButton->hide();
    pfButton->hide();
    pcButton->hide();

    //placing butons at different positions
    x = atButton->geometry().left();
    y = atButton->geometry().top();
    atButton->setGeometry(adButton->geometry());
    adButton->setGeometry(200,430,180,40);

    //Show enter display to enter player's name
    enterLabel->show();
    play1Label->show();
    p1Edit->show();
    p2Edit->show();
    p2Edit->setText(tr("Square"));
    p2Edit->setEnabled(false);
    playButton->show();
    backButton->show();
    play1Label->setText(tr("Your Name: "));
    play2Label->setText(tr("Computer Name: "));
    play2Label->show();
}

void TicTacToe::quitPressed()
{
    //delete mainwindow and quit the game
    this->close();
}

void TicTacToe::welcomeMessage()
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    welcome->start();
}

void TicTacToe::endWelcomeMessage()
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    welcome->stop();
    wLabel->hide();
    pfButton->setEnabled(true);
    pcButton->setEnabled(true);
    settingButton->setEnabled(true);
    atButton->setEnabled(true);
    adButton->setEnabled(true);
    quitButton->setEnabled(true);
    wLabel->setPixmap(QPixmap());
    QMovie *m = welcome;
    welcome = NULL;
    delete m;
    delete wLabel;
}

void TicTacToe::paintEvent(QPaintEvent *pe)
{
    //setting translator
    QTranslator ltra;
    ltra.load(langList.at(langInd));
    qApp->installTranslator(&ltra);

    if (paint == 0) {
        QWidget::paintEvent(pe); //giving control to default paint events
        QPainter painter(this);
        QPixmap pixmap(QPixmap::fromImage(QImage(":/media/rd_square/Important/Qt projects/TicTacToe/Images/background.jpg")));
        painter.drawPixmap(this->rect(), pixmap);
        QPixmap greenBoard(QPixmap::fromImage(QImage(":/media/rd_square/Important/Qt projects/TicTacToe/Images/gBoard.jpeg")));
        painter.drawPixmap(160,90,400,170, greenBoard);
    } else if (paint == 1) {
        QWidget::paintEvent(pe); //giving control to default paint events
        QPainter painter(this);
        QPixmap pixmap(QPixmap::fromImage(QImage(":/media/rd_square/Important/Qt projects/TicTacToe/Images/background.jpg")));
        painter.drawPixmap(this->rect(), pixmap);
    } else {
        QWidget::paintEvent(pe); //giving control to default paint events
        QPainter painter(this);
        QPixmap pixmap(QPixmap::fromImage(QImage(":/media/rd_square/Important/Qt projects/TicTacToe/Images/winner.jpg")));
        painter.drawPixmap(this->rect(), pixmap);
    }
}
