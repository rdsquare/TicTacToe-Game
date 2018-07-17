#include "setting.h"
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QMovie>
#include <QMessageBox>

Setting::Setting(int ind1, int ind2, int langInd, QWidget *parent)
    : QDialog(parent)
{
    //setting ui
    setupUi(this);

    lc = langInd;

    QMovie *set = new QMovie(":/media/rd_square/Important/Qt projects/TicTacToe/Images/settings.gif");
    gearLabel->setMovie(set);
    set->setScaledSize(gearLabel->size());
    set->start();

    k1 = tr("Righ-Mouse-Key");
    k2 = tr("Left-Mouse-Key");

    //setting widget of setting
    setBox->setCurrentIndex(ind1);
    keyBox->setCurrentIndex(ind2);
    langBox->setCurrentIndex(langInd);
    if (ind2 == 0) {
        oKeyLabel->setText(k2);
    } else {
        oKeyLabel->setText(k1);
    }

    //setting connections
    connect(keyBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(keyChanged(int)));
    connect(okButton, SIGNAL(clicked(bool)),
            this, SLOT(okPressed()));
}

void Setting::okPressed()
{
    int ind1 = setBox->currentIndex();
    int ind2 = keyBox->currentIndex();
    int ind3 = langBox->currentIndex();
    if (lc != langBox->currentIndex()){
        int result;
        result = QMessageBox::question(this,
                              tr("Do you want to restart? - %1").arg(qApp->applicationName()),
                              tr("Language changes is take effect after restarting the game.\n"
                                 "Do you want to restart game in order to change language?"),
                              QString("Yes, restart now!"), QString("No, I don't want to change language!"), QString(), 0,1);
        if (result == 0)
            emit settingDone(ind1, ind2, ind3, 0);
        else
            emit settingDone(ind1, ind2, lc, 1);
    }
    else
        emit settingDone(ind1, ind2, ind3, 1);
}

void Setting::keyChanged(int ind)
{
    if (ind==0)
        oKeyLabel->setText(k2);
    else
        oKeyLabel->setText(k1);
}

void Setting::paintEvent(QPaintEvent *pe)
{
    QWidget::paintEvent(pe);
    QPainter painter(this);
    QPixmap pixmap(QPixmap::fromImage(QImage(":/media/rd_square/Important/Qt projects/TicTacToe/Images/gBoard.jpeg")));
    painter.drawPixmap(this->rect(), pixmap);
}
