#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>
#include "ui_scoreboard.h"

class ScoreBoard : public QWidget, public Ui::ScoreBoard
{
    Q_OBJECT
public:
    ScoreBoard(QString pt1, QString pt2,int pc1, int pc2, QWidget *parent=0);
    void paintEvent(QPaintEvent *pe);
public slots:
    void changeTurn(int turn);
};

#endif // SCOREBOARD_H
