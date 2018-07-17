#ifndef FINALBOARD_H
#define FINALBOARD_H

#include <QWidget>
#include "ui_finalboard.h"

class FinalBoard : public QWidget, public Ui::FinalBoard
{
    Q_OBJECT
public:
    FinalBoard(QString p1Name, QString p2Name, int tm, int p1, int p2,QWidget *parent = 0);
    void paintEvent(QPaintEvent *pe);
private slots:
    void quitPressed();
    void replayPressed();
    void homePressed();
signals:
    void quitGame();
    void replayGame();
    void goToHome();
};

#endif // FINALBOARD_H
