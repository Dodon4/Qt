#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTranslator"

namespace Ui {
class MainWindow;
}

typedef struct Task
{
    QImage* imgfrom;
    int x;
    int y;
    int msize;
    QImage* imgto;
}Task;

typedef struct Res
{
    int _x;
    int _y;
    QColor color;
    QImage* imgto;
}Res;

void reducefunc(QImage &result, const Res res);

Res mapfunc(Task tasks);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    QImage* getResImg();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_actionRUS_triggered();

    void on_actionEN_triggered();

    void changeEvent(QEvent *event);
private:
    Ui::MainWindow *ui;
    QString filename;
    QImage *img;
    QImage *resimg;
    int msize;
    int thnum;
    QTranslator transl;
};



#endif // MAINWINDOW_H
