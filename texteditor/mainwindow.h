#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QApplication>
#include <QTextEdit>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
//
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_action_6_triggered();

    void on_action_7_triggered();

    void on_action_2_triggered();

    void on_action_5_triggered();

    void on_fileSave_triggered();

    void on_fileSaveAs_triggered();


    void on_ins_triggered();

    void on_cut_triggered();

    void on_copy_triggered();

    void on_povt_triggered();

    void on_otm_triggered();

    void on_action_13_triggered();

    void on_action_Qt_triggered();

    void on_action_14_triggered();

private:
    Ui::MainWindow *ui;
    MainWindow *window;
    QString currentFile;
    bool documentModified=true;
};

#endif // MAINWINDOW_H
