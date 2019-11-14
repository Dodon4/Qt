#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTime>
#include <QFileDialog>
#include <QTextCodec>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void show_label_1();
    void get_lineEdit_4();
    void get_lineEdit_3();

private:
    Ui::MainWindow *ui;
    QString filename;
    QStringList arguments;
    QProcess process;
    QTime time;
};

#endif // MAINWINDOW_H
