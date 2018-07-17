#include "scoreboard.h"
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QTimer>

ScoreBoard::ScoreBoard(QString pt1, QString pt2,int pc1, int pc2, QWidget *parent)
    : QWidget(parent)
{
    //setting ui to Score Board
    setupUi(this);

    //setting name of the player to score board
    p1->setText(pt1);
    p2->setText(pt2);

    //setting default value to match winning scoreboard
    pn1->setText(tr("%1").arg(QString::number(pc1)));
    pn2->setText(tr("%1").arg(QString::number(pc2)));
}

void ScoreBoard::changeTurn(int turn)
{
    if (turn == 0) {
        turnLabel->setText(tr("%1 turn...").arg(p1->text()));
    } else {
        turnLabel->setText(tr("%1 turn...").arg(p2->text()));
    }
}

void ScoreBoard::paintEvent(QPaintEvent *pe)
{
    //run default paintEvent of ScoreBoard
    QWidget::paintEvent(pe);
    QPainter painter(this);
    QPixmap pixmap(QPixmap::fromImage(QImage(":/media/rd_square/Important/Qt projects/TicTacToe/Images/gBoard.jpeg")));
    painter.drawPixmap(this->rect(), pixmap);
}
