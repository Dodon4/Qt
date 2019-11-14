#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"musicmodel.h"
#include "ui_mainwindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);
    void loadFile(QString filename);
    bool savefileas();
    bool saveFile();

public slots:
    void ConMenu(QPoint point);
    void documentModified();
    void activeAction(QModelIndex index);

private slots:
    void on_actionOpen_triggered();
    bool on_actionSave_triggered();
    void on_actionClose_triggered();
    void on_actionArtist_triggered();
    void on_actionAlbum_triggered();
    void on_actionSong_triggered();
    void on_actionChang_triggered();
    void on_actionDel_triggered();
    bool on_actionSaveAs_triggered();

private:
    Ui::MainWindow *ui;
    MusicModel *model;
    QString curFile;

};

#endif // MAINWINDOW_H
