#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QStringList>
#include "ui_board.h"
#include <QMovie>
#include <QEvent>

class Board : public QWidget, public Ui::Board
{
    Q_OBJECT
public:
    Board(QString name1, QString name2, int setInd, int keyInd, int firstTurn,int lg, QWidget *parent=0);
    void paintEvent(QPaintEvent *pe);
    bool eventFilter(QObject *target, QEvent *event);
signals:
    void turnChanged(int turn);
    void matchFinished(int player = -1);
private:
    void setWidgets();
    bool doChecking();
    void disableAll();

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
    int langInd;
    QStringList langList;
};

#endif // BOARD_H
