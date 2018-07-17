#include "developer.h"
#include <QMovie>
#include <QPainter>
#include <QPixmap>
#include <QImage>

Developer::Developer(QWidget *parent)
    : QDialog(parent)
{
    //setting ui to this widget
    setupUi(this);

    //setting animation
    QMovie *movie = new QMovie(":/media/rd_square/Important/Qt projects/TicTacToe/Images/about.gif");
    aboutLabel->setMovie(movie);
    movie->setScaledSize(aboutLabel->size());
    movie->start();

    connect(okButton, SIGNAL(clicked(bool)),
            this, SLOT(okPressed()));
}

void Developer::paintEvent(QPaintEvent *pe)
{
    QWidget::paintEvent(pe);
    QPainter painter(this);
    QPixmap pixmap(QPixmap::fromImage(QImage(":/media/rd_square/Important/Qt projects/TicTacToe/Images/gBoard.jpeg")));
    painter.drawPixmap(this->rect(), pixmap);
}

void Developer::okPressed()
{
    emit okAccepted();
}
