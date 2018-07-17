#include "about.h"
#include <QPainter>
#include <QPixmap>
#include <QImage>

About::About(QWidget *parent)
    : QDialog(parent)
{
    //setting ui to this widget
    setupUi(this);

    connect(okButton, SIGNAL(clicked(bool)),
            this, SLOT(okPressed()));
}

void About::paintEvent(QPaintEvent *pe)
{
    QWidget::paintEvent(pe);
    QPainter painter(this);
    QPixmap pixmap(QPixmap::fromImage(QImage(":/media/rd_square/Important/Qt projects/TicTacToe/Images/gBoard.jpeg")));
    painter.drawPixmap(this->rect(), pixmap);
}

void About::okPressed()
{
    emit okAccepted();
}
