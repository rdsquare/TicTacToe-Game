#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include "ui_setting.h"
#include <QStringList>

class Setting : public QDialog, public Ui::Setting
{
    Q_OBJECT
public:
    Setting(int ind1, int ind2,int langInd, QWidget *parent=0);
    void paintEvent(QPaintEvent* pe);
private slots:
    void okPressed();
    void keyChanged(int ind);
signals:
    void settingDone(int ind1, int ind2, int ind3, int langc);
private:
    QString k1;
    QString k2;
    int lc;
};

#endif // SETTING_H
