#include "board.h"
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include <QBrush>
#include <QMouseEvent>
#include <QDebug>
#include <QTranslator>

Board::Board(QString name1, QString name2, int setInd, int keyInd, int firstTurn,int lg, QWidget *parent)
    : QWidget(parent)
{
    //setting ui to this widget
    setupUi(this);

    //settings labels
    labels[0] = t0;
    labels[1] = t1;
    labels[2] = t2;
    labels[3] = t3;
    labels[4] = t4;
    labels[5] = t5;
    labels[6] = t6;
    labels[7] = t7;
    labels[8] = t8;
    name[0] = name1;
    name[1] = name2;

    //setting language index
    langInd = lg; //for setting language of game

    //setting language for game
    langList << ":/media/rd_square/Important/Qt projects/TicTacToe/translations/tictactoe_en_us.qm"
            << ":/media/rd_square/Important/Qt projects/TicTacToe/translations/tictactoe_hi.qm";

    //setting variables
    setID = setInd;
    keyID = keyInd;
    currTurn = firstTurn;
    dir = ":/media/rd_square/Important/Qt projects/TicTacToe/Images/";

    //setting widgets of Board
    setWidgets();

    QStringList tempList;
    switch(setID) {
    case 0:
        tempList = ox;
        break;
    case 1:
        tempList = fv;
        break;
    case 2:
        tempList = mal;
        break;
    case 3:
        tempList = an;
        break;
    }
    qsrand(time(0)); //initializing random seed
    int temp = qrand() % tempList.length(); //generating random numbers
    int temp1 = qrand() % tempList.length(); //generating random numbers
    if ((temp == temp1) && (temp == (tempList.length()-1))) {
        temp1--;
    } else if (temp == temp1){
        temp1++;
    }
    anim1 = dir + tempList[temp];
    anim2 = dir + tempList[temp1];
}

bool Board::doChecking() {
    for (int i = 0; i < 3; i++) {
        if ((ticTac[i][0] == ticTac[i][1]) && (ticTac[i][2] == currTurn)) {
            if (ticTac[i][0] == ticTac[i][2]) {
                for (int k=0; k < 9; k++) {
                    labels[k]->removeEventFilter(this);
                }
                labels[i*3+0]->setStyleSheet("QLabel { background-color: yellow }");
                labels[i*3+1]->setStyleSheet("QLabel { background-color: yellow }");
                labels[i*3+2]->setStyleSheet("QLabel { background-color: yellow }");
                return true;
            }
        }
        if ((ticTac[0][i] == ticTac[1][i]) && (ticTac[2][i] == currTurn)) {
            if (ticTac[0][i] == ticTac[2][i]) {
                for (int k=0; k < 9; k++) {
                    labels[k]->removeEventFilter(this);
                }
                labels[i]->setStyleSheet("QLabel { background-color: yellow }");
                labels[3+i]->setStyleSheet("QLabel { background-color: yellow }");
                labels[6+i]->setStyleSheet("QLabel { background-color: yellow }");
                return true;
            }
        }
    }
    if ((ticTac[0][0] == ticTac[1][1]) && (ticTac[2][2] == currTurn)) {
        if (ticTac[0][0] == ticTac[2][2]){
            for (int k=0; k < 9; k++) {
                labels[k]->removeEventFilter(this);
            }
            labels[0]->setStyleSheet("QLabel { background-color: yellow }");
            labels[4]->setStyleSheet("QLabel { background-color: yellow }");
            labels[8]->setStyleSheet("QLabel { background-color: yellow }");
            return true;
        }
    }
    if ((ticTac[0][2] == ticTac[1][1]) && (ticTac[2][0] == currTurn)) {
        if (ticTac[0][2] == ticTac[2][0]) {
            for (int k=0; k < 9; k++) {
                labels[k]->removeEventFilter(this);
            }
            labels[2]->setStyleSheet("QLabel { background-color: yellow }");
            labels[4]->setStyleSheet("QLabel { background-color: yellow }");
            labels[6]->setStyleSheet("QLabel { background-color: yellow }");
            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j=0; j < 3; j++) {
            if ((ticTac[i][j] != 0) && (ticTac[i][j] != 1)) {
                return false;
            }
        }
    }
    for (int i=0; i<9; i++) {
        labels[i]->setStyleSheet("QLabel { background-color: red }");
    }
    currTurn = -1;
    return true;
}

void Board::setWidgets()
{
    //installing event filter to all squares
    for (int i=0; i < 9; i++) {
        labels[i]->installEventFilter(this);
    }

    //setting all the string lists
    ox.append("ohw.gif");
    ox.append("quit1.png");

    fv.append("apple.gif");
    fv.append("banana.gif");
    fv.append("cherry.gif");
    fv.append("cocoa.gif");
    fv.append("grape.gif");
    fv.append("lemon.gif");
    fv.append("melon.gif");
    fv.append("peach.gif");
    fv.append("pear.gif");
    fv.append("pineapple.gif");
    fv.append("tomato.gif");
    fv.append("watermelon.gif");

    mal.append("bug.gif");
    mal.append("dianosor.gif");
    mal.append("dog.gif");
    mal.append("goat.gif");
    mal.append("ostrich.gif");
    mal.append("tiger.gif");

    an.append("apple.gif");
    an.append("banana.gif");
    an.append("cherry.gif");
    an.append("cocoa.gif");
    an.append("grape.gif");
    an.append("lemon.gif");
    an.append("melon.gif");
    an.append("peach.gif");
    an.append("pear.gif");
    an.append("pineapple.gif");
    an.append("tomato.gif");
    an.append("watermelon.gif");
    an.append("bug.gif");
    an.append("dianosor.gif");
    an.append("dog.gif");
    an.append("goat.gif");
    an.append("ostrich.gif");
    an.append("tiger.gif");
    an.append("alcohol");

    for (int i=0; i<3; i++) {
        for (int j=0; j<3;j++) {
            ticTac[i][j] = 10;
        }
    }
}

void Board::disableAll()
{
    for (int i=0;i < 9; i++) {
        labels[i]->removeEventFilter(this);
    }
}

bool Board::eventFilter(QObject *target, QEvent *event)
{
    for (int i=0; i<9; i++) {
        if(target == labels[i] && event->type() == QEvent::MouseButtonPress){
            //setting translator
            QTranslator ltra;
            ltra.load(langList.at(langInd));
            qApp->installTranslator(&ltra);

            QMouseEvent* me = static_cast<QMouseEvent*>(event);
            if(me->button() == Qt::RightButton){
                if ((currTurn == 0) && (keyID == 0)) {
                    movie = new QMovie(anim1);
                    movie->setScaledSize(labels[i]->size());
                    labels[i]->setMovie(movie);
                    labels[i]->removeEventFilter(this);
                    movie->start();
                    int row = (int) i / 3;
                    int col = i % 3;
                    ticTac[row][col] = 0;
                    if (doChecking()) {
                        emit matchFinished(currTurn);
                        disableAll();
                        return true;
                    }
                    currTurn = 1;
                    emit turnChanged(currTurn);
                } else if ((currTurn == 1) && (keyID == 1) ){
                    movie = new QMovie(anim2);
                    labels[i]->setMovie(movie);
                    movie->setScaledSize(labels[i]->size());
                    movie->start();
                    labels[i]->removeEventFilter(this);
                    int row = (int) i / 3;
                    int col = i % 3;
                    ticTac[row][col] = 1;
                    if (doChecking()) {
                        emit matchFinished(currTurn);
                        return true;
                    }
                    currTurn = 0;
                    emit turnChanged(currTurn);
                } else {
                    QMessageBox::information(this, tr("Wrong Key Pressed! - %1").arg(qApp->applicationName()),
                                             tr("Current turn is of %1. Kindly press Left-Mouse-Button to select appropriate Box."
                                                "And of course do not select already selected boxes.").arg(name[currTurn]),
                                             QMessageBox::Ok | QMessageBox::Default);
                    return true;
                }
            } else if (me->button() == Qt::LeftButton) {
                if ((currTurn == 0) && (keyID == 1) ) {
                    movie = new QMovie(anim1);
                    labels[i]->setMovie(movie);
                    movie->setScaledSize(labels[i]->size());
                    labels[i]->removeEventFilter(this);
                    movie->start();
                    int row = (int) i / 3;
                    int col = i % 3;
                    ticTac[row][col] = 0;
                    if (doChecking()) {
                        emit matchFinished(currTurn);
                        return true;
                    }
                    currTurn = 1;
                    emit turnChanged(currTurn);
                } else if ((currTurn == 1) && (keyID == 0) ) {
                    movie = new QMovie(anim2);
                    labels[i]->setMovie(movie);
                    movie->setScaledSize(labels[i]->size());
                    labels[i]->removeEventFilter(this);
                    movie->start();
                    int row = (int) i / 3;
                    int col = i % 3;
                    ticTac[row][col] = 1;
                    if (doChecking()) {
                        emit matchFinished(currTurn);
                        return true;
                    }
                    currTurn = 0;
                    emit turnChanged(currTurn);
                } else {
                    QMessageBox::information(this, tr("Wrong Key Pressed! - %1").arg(qApp->applicationName()),
                                             tr("Current turn is of %1. Kindly press Right-Mouse-Button to select appropriate Box."
                                                "And of course do not select already selected boxes.").arg(name[currTurn]),
                                             QMessageBox::Ok | QMessageBox::Default);
                    return true;
                }
            }
        }
    }
    return QWidget::eventFilter(target, event);
}

void Board::paintEvent(QPaintEvent *pe)
{
    //wetting default paintEvent()
    QWidget::paintEvent(pe);
    QPainter painter(this);
    /*QBrush brush(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(100,0,5,300);
    painter.drawRect(194,0,5,300);
    painter.drawRect(0,99,300,5);
    painter.drawRect(0,194,300,5);
    painter.drawRect(0,0,300,9);
    painter.drawRect(0,0,9,300);
    painter.drawRect(0,291,300,9);
    painter.drawRect(291,0,9,300);*/
    QPixmap pixmap(QPixmap::fromImage(QImage(":/media/rd_square/Important/Qt projects/TicTacToe/Images/gBoard.jpeg")));
    painter.drawPixmap(this->rect(),pixmap);
}
