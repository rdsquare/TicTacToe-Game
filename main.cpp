#include "tictactoe.h"
#include <QApplication>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/media/rd_square/Important/Qt projects/TicTacToe/Images/tacLogo.png").scaled(250,250, Qt::IgnoreAspectRatio));
    splash->show();

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;

    splash->showMessage(QObject::tr("Opening Tic-Tac-Toe..."), topRight, Qt::white);


    splash->showMessage(QObject::tr("Lading game modules..."), topRight, Qt::white);
    TicTacToe *game = new TicTacToe(0,3,1);
    game->count = -1;

    game->show();
    splash->finish(game);
    delete splash;

    return a.exec();
}
