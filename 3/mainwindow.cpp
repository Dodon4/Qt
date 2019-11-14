#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFontDialog>
#include <QSettings>
#include <QFileDialog>
#include <QTextStream>
#include <QFileInfo>

MainWindow::MainWindow(const QString &fileName, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFileName(fileName);
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);

    QSettings settings;
    QFont font = settings.value("font", QApplication::font()).value<QFont>();
    ui->textEdit->setFont(font);
    loadFile(fileName);
    qttranslator.load(QString("qttranslate_Ru"));
    qApp->installTranslator(&qttranslator);
}  
void MainWindow::on_changeEn_triggered()
{
    qttranslator.load(QString("qttranslate_En"));
    qApp->installTranslator(&qttranslator);
    ui->changeRu->setEnabled(true);
    ui->changeEn->setEnabled(false);
}

void MainWindow::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
       ui->retranslateUi(this);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    MainWindow *s=new MainWindow;
    s->show();
}

void MainWindow::on_actionAbout_triggered()
{
   QMessageBox::about(this, tr("Программа для работы с текстом"), tr("О программе"));
}

void MainWindow::on_actionAboutQt_triggered()
{
     qApp->aboutQt();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
     ui->actionCopy->setEnabled(b);
     ui->actionCut->setEnabled(b);
}

void MainWindow::on_textEdit_undoAvailable(bool b)
{
    ui->actionUndo->setEnabled(b);
}

void MainWindow::on_textEdit_redoAvailable(bool b)
{
    ui->actionRedo->setEnabled(b);
}

void MainWindow::loadFile(const QString &fileName)
{
    if(fileName.isEmpty())
    {
        setFileName(QString());
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Файл невозможно открыть"), QMessageBox::Ok);
        setFileName(QString());
        return;
    }
    else
    {
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
        setFileName(fileName);
        setWindowModified(false);
    }


}


void MainWindow::on_actionClose_triggered()
{
    this->close();
}

void MainWindow::on_actionExit_triggered()
{
    qApp->closeAllWindows();
}

void MainWindow::documentModified()
{
    setWindowModified(true);
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont init (QApplication::font());
    QFont font = QFontDialog::getFont(
                        &ok, init, this);
    if (ok) {
        ui->textEdit->setFont(font);

        QSettings settings(QApplication::organizationName(), QApplication::applicationName());

        settings.setValue("font", font);
     } else {
     }
}

void MainWindow::setFileName(const QString &name)
{
    m_fileName = name;
    setWindowTitle(
                   QString("%1[*] ­ %2")
                   .arg(m_fileName.isNull()?"новый":QFileInfo(m_fileName).fileName())
                   .arg(QApplication::applicationName())
                   );
}

bool MainWindow::saveFile()
{
    if(m_fileName.isNull())
    {
        return saveFileAs();
    }
    else
    {
        QFile file(m_fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Ошибка"), tr("Невозможно открыть файл"), QMessageBox::Ok);
            setFileName(QString());
            return false;
        }
        else
        {
            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
            file.close();
            setWindowModified(false);
            return true;
        }


    }
}
void MainWindow::on_actionSave_triggered()
{
    saveFile();
}

void MainWindow::on_actionSaveAs_triggered()
{
    saveFileAs();
}



void MainWindow::closeEvent(QCloseEvent *e){
    if(isWindowModified()){
        switch(QMessageBox::warning(this, "Document Modified","The document has been modified."
                                    "Do you want to save your changes?\n"
                                    "You will lose and unsaved changes.",
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                    QMessageBox::No)){
            case QMessageBox::Yes:
                saveFile();
                e->accept();
                break;
            case QMessageBox::No:
                e->accept();
                break;
            case QMessageBox::Cancel:
                e->ignore();
                break;
        }
    }
    else
    {
        e->accept();
    }
}

void MainWindow::on_changeRu_triggered()
{
    qttranslator.load(QString("qttranslate_Ru"));
    qApp->installTranslator(&qttranslator);
    ui->changeRu->setEnabled(false);
    ui->changeEn->setEnabled(true);
}



void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Открыть документ", QDir::currentPath(), "Text documents(*.txt)");
    if(fileName.isNull())
    {
        return;
    }
    if(m_fileName.isNull() && !isWindowModified())
    {
        loadFile(fileName);
    }
    else {
        MainWindow *qmw = new MainWindow(fileName, 0);
        qmw->show();
    }
}

bool MainWindow::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить документ", m_fileName.isNull()?QDir::currentPath():m_fileName,"Text documents (*.txt)");
    if(fileName.isNull())
    {
        return false;
    }
    else
    {
        setFileName(fileName);
        return saveFile();
    }

}

