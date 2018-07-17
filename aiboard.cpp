#include "aiboard.h"
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include <QBrush>
#include <QMouseEvent>
#include <QStack>
#include <QDebug>
#include <QTranslator>

AiBoard::AiBoard(QString name1, QString name2, int setInd, int keyInd, int firstTurn,int lg, QWidget *parent)
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

    isFirstPlay = true;
    totalPlay = 0;

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

    if (currTurn == 1){
        playAi();
    }
}

void AiBoard::disableAll()
{
    for (int i=0;i < 9; i++) {
        labels[i]->removeEventFilter(this);
    }
}

bool AiBoard::doChecking() {
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

void AiBoard::setWidgets()
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

    //setting variables for ai
    array = new int**[3];
    for (int i= 0; i<3; i++) {
        array[i] = new int*[3];
    }

    for (int i = 0; i<3; i++) {
        for (int j=0;j < 3; j++) {
            int* temp = new int;
            *temp = 10;
            array[i][j] = temp;
        }
    }

    listNode = new Base*[5];
    for (int i= 0;i<5;i++) {
        listNode[i] = new Base();
    }

    listNode[0]->insertValue(array[0][1], array[0][2]); //0th node to 1 and 2
    listNode[0]->insertValue(array[1][1], array[2][2]); //0th node to 4 and 8
    listNode[0]->insertValue(array[1][0], array[2][0]); //0th node to 3 and 6
    listNode[0]->data = array[0][0]; //0th node 0th list

    listNode[1]->insertValue(array[1][1], array[2][1]); // 1st node to 4 and 7
    listNode[1]->data = array[0][1]; //1st node to 1st list

    listNode[2]->insertValue(array[1][1], array[2][0]); //2nd node to 4 and 6
    listNode[2]->insertValue(array[1][2], array[2][2]); //2nd node to 4 and 8
    listNode[2]->data = array[0][2]; //2nd node to 2nd list

    listNode[3]->insertValue(array[1][1], array[1][2]); //3rd node to 4 and 5
    listNode[3]->data = array[1][0]; //3rd node to 3rd list

    listNode[4]->insertValue(array[2][1], array[2][2]); //6th node to 7 and 8
    listNode[4]->data = array[2][0]; //6th node 4th list
}

void AiBoard::paintEvent(QPaintEvent *pe)
{
    //wetting default paintEvent()
    QWidget::paintEvent(pe);
    QPainter painter(this);
    QPixmap pixmap(QPixmap::fromImage(QImage(":/media/rd_square/Important/Qt projects/TicTacToe/Images/gBoard.jpeg")));
    painter.drawPixmap(this->rect(),pixmap);
}

bool AiBoard::eventFilter(QObject *target, QEvent *event)
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
                    labels[i]->removeEventFilter(this);
                    totalPlay++;
                    movie = new QMovie(anim1);
                    movie->setScaledSize(labels[i]->size());
                    labels[i]->setMovie(movie);
                    movie->start();
                    int row = (int) i / 3;
                    int col = i % 3;
                    *array[row][col] = ticTac[row][col] = 0;
                    if (doChecking()) {
                        emit matchFinished(currTurn);
                        disableAll();
                        return true;
                    }
                    currTurn = 1;
                    emit turnChanged(currTurn);
                    playAi();
                }else {
                    QMessageBox::critical(this, tr("Wrong Key Pressed! - %1").arg(qApp->applicationName()),
                                             tr("Current turn is of %1. Kindly press Left-Mouse-Button to select appropriate Box.").arg(name[currTurn]),
                                             QMessageBox::Ok | QMessageBox::Default);
                    return true;
                }
            } else if (me->button() == Qt::LeftButton) {
                if ((currTurn == 0) && (keyID == 1)) {
                    totalPlay++;
                    labels[i]->removeEventFilter(this);
                    movie = new QMovie(anim1);
                    labels[i]->setMovie(movie);
                    movie->setScaledSize(labels[i]->size());
                    movie->start();
                    int row = (int) i / 3;
                    int col = i % 3;
                    *array[row][col] = ticTac[row][col] = 0;
                    if (doChecking()) {
                        emit matchFinished(currTurn);
                        return true;
                    }
                    currTurn = 1;
                    emit turnChanged(currTurn);
                    playAi();
                }else {
                    QMessageBox::critical(this, tr("Wrong Key Pressed! - %1").arg(qApp->applicationName()),
                                             tr("Current turn is of %1. Kindly press Right-Mouse-Button to select appropriate Box.").arg(name[currTurn]),
                                             QMessageBox::Ok | QMessageBox::Default);
                    return true;
                }
            }
        }
    }
    return QWidget::eventFilter(target, event);
}

void AiBoard::playAi()
{
    if((totalPlay == 0) && isFirstPlay) {
        *(listNode[3]->start->p1) = 1;
    }

    if ((totalPlay != 0) && isFirstPlay) {
        if (*(listNode[3]->start->p1) == 10){
            *(listNode[3]->start->p1) = 1;
        } else {
            QStack<int*> mainStack;
            if ((*array[0][0] == 10) && (*array[2][2] == 10)) {
                mainStack.push(array[0][0]);
                mainStack.push(array[2][2]);
            }
            if ((*array[0][2] == 10) && (*array[2][0])) {
                mainStack.push(array[0][2]);
                mainStack.push(array[2][0]);
            }
            int* change = mainStack.pop();
            *change = 1;
        }
    }

    isFirstPlay = false;

    if (totalPlay == 8) {
        for (int i=0; i<3; i++) {
            for (int j=0; j < 3; j++) {
                if (*array[i][j] == 10){
                    *array[i][j] = 1;
                }
            }
        }
    }

    if(totalPlay > 1 && totalPlay < 8) {
        //checking for ai winning
        int done = 0;
        for (int i =0;i<5;i++) {
            Node* tempNode = listNode[i]->start;
            int out = 0;
            for (int j =0; j<listNode[i]->count; j++) {
                if (*listNode[i]->data == 10) {
                    if (*tempNode->p1 == 1 && *tempNode->p2 == 1){
                        out = 1;
                        *listNode[i]->data = 1;
                        break;
                    }
                    tempNode = tempNode->next;
                }
            }
            if (out == 1){
                done = 1;
                break;
            }
        }

        if (done == 0) {
            for (int i =0;i<5;i++) {
                Node* tempNode = listNode[i]->start;
                int out = 0;
                for (int j =0; j<listNode[i]->count; j++) {
                    if (*listNode[i]->data == 1) {
                        if (*tempNode->p1 == 10 && *tempNode->p2 == 1){
                            out = 1;
                            *tempNode->p1 = 1;
                            break;
                        }
                        if (*tempNode->p2 == 10 && *tempNode->p1 == 1) {
                            out = 1;
                            *tempNode->p2 = 1;
                            break;
                        }
                        tempNode = tempNode->next;
                    }
                }
                if (out == 1){
                    done = 1;
                    break;
                }
            }
        }

        //checking to restrict player winning
        if (done == 0) {
            for (int i =0;i<5;i++) {
                Node* tempNode = listNode[i]->start;
                int out = 0;
                for (int j =0; j<listNode[i]->count; j++) {
                    if (*listNode[i]->data == 10) {
                        if (*tempNode->p1 == 0 && *tempNode->p2 == 0){
                            out = 1;
                            *listNode[i]->data = 1;
                            break;
                        }
                        tempNode = tempNode->next;
                    }
                }
                if (out == 1){
                    done = 1;
                    break;
                }
            }
        }

        if (done == 0) {
            for (int i =0;i<5;i++) {
                Node* tempNode = listNode[i]->start;
                int out = 0;
                for (int j =0; j<listNode[i]->count; j++) {
                    if (*listNode[i]->data == 0) {
                        if (*tempNode->p1 == 10 && *tempNode->p2 == 0){
                            out = 1;
                            *tempNode->p1 = 1;
                            break;
                        }
                        if (*tempNode->p2 == 10 && *tempNode->p1 == 0) {
                            out = 1;
                            *tempNode->p2 = 1;
                            break;
                        }
                        tempNode = tempNode->next;
                    }
                }
                if (out == 1){
                    done = 1;
                    break;
                }
            }
        }

        //checking for blank corner point
        if (done == 0) {
            QStack<int*> mainStack;
            QStack<int*>bufferStack;
            if (*array[0][0] == 10) {
                if (*array[2][2] == 10){
                    mainStack.push(array[0][0]);
                    mainStack.push(array[2][2]);
                } else {
                    bufferStack.push(array[0][0]);
                }
            } else {
                if (*array[2][2] == 10){
                    bufferStack.push(array[2][2]);
                }
            }
            if (*array[0][2] == 10) {
                if (*array[2][0] == 10){
                    mainStack.push(array[0][2]);
                    mainStack.push(array[2][0]);
                } else {
                    bufferStack.push(array[0][2]);
                }
            } else {
                if (*array[2][0] == 10){
                    bufferStack.push(array[2][0]);
                }
            }

            if (!mainStack.isEmpty()) {
                int* temp = mainStack.pop();
                *temp = 1;
                done = 1;
            } else if (!bufferStack.isEmpty()){
                int* temp = bufferStack.pop();
                *temp  = 1;
                done = 1;
            }
        }

        if (done == 0) {
            //checking for edge points
            QStack<int*> mainStack;
            QStack<int*>bufferStack;
            if (*array[0][1] == 10) {
                if (*array[2][1] == 10){
                    mainStack.push(array[0][1]);
                    mainStack.push(array[2][1]);
                } else {
                    bufferStack.push(array[0][1]);
                }
            } else {
                if (*array[2][1] == 10){
                    bufferStack.push(array[2][1]);
                }
            }
            if (*array[1][0] == 10) {
                if (*array[1][2] == 10){
                    mainStack.push(array[1][0]);
                    mainStack.push(array[1][2]);
                } else {
                    bufferStack.push(array[1][0]);
                }
            } else {
                if (*array[1][2] == 10){
                    bufferStack.push(array[1][2]);
                }
            }

            if (!mainStack.isEmpty()) {
                int* temp = mainStack.pop();
                *temp = 1;
            } else {
                int* temp = bufferStack.pop();
                *temp  = 1;
            }
        }
    }

    //all combinations are done till now, Now set animation and check for winning
    for (int i= 0; i<3; i++) {
        int out = 0;
        for (int j=0; j<3; j++) {
            if (*array[i][j] != ticTac[i][j]){
                int k = 3*i + j;
                labels[k]->removeEventFilter(this);
                ticTac[i][j] = *array[i][j];
                totalPlay++;
                movie = new QMovie(anim2);
                movie->setScaledSize(labels[k]->size());
                labels[k]->setMovie(movie);
                movie->start();
                out = 1;
                break;
            }
        }
        if (out == 1)
            break;
    }

    if (doChecking()) {
        emit matchFinished(currTurn);
        disableAll();
        return;
    }
    currTurn = 0;
    emit turnChanged(currTurn);
}
