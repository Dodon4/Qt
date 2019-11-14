#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "game.h"
#include "paintpuz.h"
#include "puzzle.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    game* scene;
    QGraphicsView* view;
    Q_OBJECT
QPixmap *vs;
public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //QSize fieldSize();
   // QString imgName();
   void setName(QString fileName);
    void setScene(/*QSize size, */game* newScene, QGraphicsView* view);
    QString imgName();
private slots:
    void on_pushButton_3_clicked();

    //QSize on_pushButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
       QString fileName;




};

#endif // MAINWINDOW_H
