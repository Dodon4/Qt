#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>


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

    void on_find_clicked();

    void on_start_clicked();

    void producerUpdateBuffer(const QString &text);

    void consumerUpdateBuffer(const QString &text, char sim, int cycleCount);

private:
    Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H
