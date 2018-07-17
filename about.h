#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include "ui_about.h"

class About : public QDialog, public Ui::About
{
    Q_OBJECT
public:
    About(QWidget *parent=0);
    void paintEvent(QPaintEvent *pe);
private slots:
    void okPressed();
signals:
    void okAccepted();
};

#endif // ABOUT_H
