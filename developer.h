#ifndef DEVELOPER_H
#define DEVELOPER_H

#include <QDialog>
#include "ui_developer.h"

class Developer : public QDialog, public Ui::Developer
{
    Q_OBJECT
public:
    Developer(QWidget *parent=0);
    void paintEvent(QPaintEvent *pe);
private slots:
    void okPressed();
signals:
    void okAccepted();
};

#endif // DEVELOPER_H
