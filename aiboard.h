#ifndef AIBOARD_H
#define AIBOARD_H

#include <QWidget>
#include "ui_board.h"
#include <QMovie>
#include <QEvent>
#include <QStringList>

struct Node {
    int* p1;
    int* p2;
    Node* next;
};

class Base {
public:
    int count;
    int* data;
    Node* start;
    Node* last;

    Base() {
        count = 0;
        start = NULL;
        last = NULL;
    }
    void insertValue(int* x, int* y) {
        if (count == 0){
            last = new Node;
            last->next = NULL;
            start = last;
        } else {
            last->next = new Node;
            last = last->next;
        }
        count++;
        last->p1 = x;
        last->p2 = y;
    }
};

class AiBoard : public QWidget, public Ui::Board
{
    Q_OBJECT
public:
    AiBoard(QString name1, QString name2, int setInd, int keyInd, int firstTurn,int lg, QWidget *parent=0);
    void paintEvent(QPaintEvent *pe);
    bool eventFilter(QObject *target, QEvent *event);
signals:
    void turnChanged(int turn);
    void matchFinished(int player = -1);
private:
    void setWidgets();
    bool doChecking();
    void disableAll();
    void playAi();

    int setID;
    int keyID;
    int currTurn;
    int ticTac[3][3];
    QString name[2];
    QString anim1;
    QString anim2;
    QString dir;
    QStringList ox;
    QStringList fv;
    QStringList mal;
    QStringList an;
    QMovie *movie;
    QLabel* labels[9];
    Base** listNode;
    int*** array;
    int totalPlay; //for first turn;
    bool isFirstPlay; //for computer's first turn
    int langInd;
    QStringList langList;
};

#endif // AIBOARD_H
