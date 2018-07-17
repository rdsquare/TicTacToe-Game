#include "finalboard.h"
#include <QPainter>
#include <QPixmap>
#include <QImage>

FinalBoard::FinalBoard(QString p1Name, QString p2Name, int tm, int p1, int p2,QWidget *parent)
    : QWidget(parent)
{
    //setting ui file to widget
    setupUi(this);

    //setting labels
    tmScore->setText(QString::number(tm));
    p1Score->setText(QString::number(p1));
    p2Score->setText(QString::number(p2));
    p1Label->setText(tr("%1 won").arg(p1Name));
    p2Label->setText(tr("%1 won").arg(p2Name));
    mdLabel->setText(tr("%1 match(s) are draw.").arg(QString::number(tm-p1-p2)));

    //setting connections
    connect(playButton, SIGNAL(clicked(bool)),
            this, SLOT(replayPressed()));
    connect(homeButton, SIGNAL(clicked(bool)),
            this, SLOT(homePressed()));
    connect(quitButton, SIGNAL(clicked(bool)),
            this , SLOT(quitPressed()));
}

void FinalBoard::replayPressed()
{
   emit replayGame();
}

void FinalBoard::homePressed()
{
    emit goToHome();
}

void FinalBoard::quitPressed()
{
    emit quitGame();
}

void FinalBoard::paintEvent(QPaintEvent *pe)
{
    QWidget::paintEvent(pe);
    QPainter painter(this);
    QPixmap pixmap(QPixmap::fromImage(QImage(":/media/rd_square/Important/Qt projects/TicTacToe/Images/gBoard.jpeg")));
    painter.drawPixmap(this->rect(), pixmap);
}
