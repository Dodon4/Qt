#include "mainwindow.h"
#include <QApplication>
#include "puzzle.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDialog>
#include <QFileDialog>
#include "paintpuz.h"
#include "game.cpp"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsView* gv = new QGraphicsView;
    QGraphicsScene gs;
    game* gs1 = new game;
    puzzle p;

    QSize size=p.Value();
    MainWindow cd;
    gv->setScene(gs1);
    cd.setScene(/*size, */gs1, gv);
    cd.show();
    return a.exec();
}
