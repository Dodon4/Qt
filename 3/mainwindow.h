#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &fileName=QString(), QWidget *parent=0);
    ~MainWindow();
    void setCurrentFile(const QString &fileName);

private slots:
    void on_actionNew_triggered();

    void on_actionClose_triggered();

    void on_actionExit_triggered();

    void documentModified();

    void on_actionOpen_triggered();
    bool saveFile();
    bool saveFileAs();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_changeRu_triggered();

    void on_changeEn_triggered();
    void on_actionFont_triggered();

    void on_actionAbout_triggered();

    void on_actionAboutQt_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_textEdit_copyAvailable(bool b);
    void on_textEdit_undoAvailable(bool b);
    void on_textEdit_redoAvailable(bool b);

private:
    Ui::MainWindow *ui;
    QString m_fileName;
    void loadFile(const QString &fileName);
    void setFileName(const QString &);
    QTranslator qttranslator;




protected:
    void closeEvent(QCloseEvent *e);
    void changeEvent(QEvent * e) override;
};

#endif // MAINWINDOW_H
