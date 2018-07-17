#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QMainWindow>
#include <QWidget>
#include <QMovie>
#include "ui_tictactoe.h"
#include "scoreboard.h"
#include "setting.h"
#include "board.h"
#include "developer.h"
#include "about.h"
#include "finalboard.h"
#include <QStringList>
#include <QTranslator>
#include "aiboard.h"

class TicTacToe : public QMainWindow, public Ui::TicTacToe
{
    Q_OBJECT
public:
    TicTacToe(int lg,int s, int k , QWidget *parent=0);
    void paintEvent(QPaintEvent *pe);

    int count;
private slots:
    void welcomeMessage();
    void endWelcomeMessage();
    void quitPressed();
    void pfPressed();
    void pcPressed();
    void adPressed();
    void deleteDev();
    void atPressed();
    void deleteAbout();
    void playPressed();
    void settingReceived(int ind1, int ind2, int ind3, int langc);
    void settingPressed();
    void gameFinished(int player);
    void gameWin();
    void homePressed();
    void stopWinningAnimation();
    void replayGame();
    void backPressed();
private:
    QMovie *welcome;
    QMovie *animate;
    ScoreBoard *scoreBoard;
    Developer *devolper;
    FinalBoard *finalBoard;
    AiBoard *aiBoard;
    About *about;
    Board *board;
    int paint;
    QString play1Name;
    QString play2Name;
    int play1Num;
    int play2Num;
    int matchPlayed;
    int play1Win;
    int play2Win;
    int matchDraw;
    int set;
    int key;
    Setting *setting;
    int currTurn;
    QLabel *winning;
    int x;
    int y;
    int playWith;
    QStringList langList;
    int langInd;
};

struct Trans {
    QTranslator langTrans;
};

#endif // TICTACTOE_H
