#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QApplication>
#include <QTextBrowser>
#include <QFile>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_6_triggered()
{
    if (!ui->textEdit->document()->isModified())
            QApplication::closeAllWindows();
    const QMessageBox::StandardButton ret =
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("Документ был изменен.\n"
                                "Вы хотите сохранить изменения?"),
                             QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        on_fileSave_triggered();
    if (ret == QMessageBox::No)
        QApplication::closeAllWindows();

}


void MainWindow::on_action_7_triggered()
{
    window = new MainWindow(this);
    window->show();
}

void MainWindow::on_action_2_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Внимание", "Невозможно открыть файл: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_action_5_triggered()
{const QMessageBox::StandardButton ret =
            QMessageBox::warning(this, QCoreApplication::applicationName(),
                                 tr("Документ был изменен.\n"
                                    "Вы хотите сохранить изменения?"),
                                 QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
    if (!ui->textEdit->document()->isModified())
            this->close();
    else{
    if (ret == QMessageBox::Save)
        on_fileSave_triggered();
    if (ret == QMessageBox::No)
         this->close();
    }
}

void MainWindow::on_fileSave_triggered()
{
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Сохранить");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,  "Внимание", "Невозможно сохранить файл: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();

}


void MainWindow::on_fileSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить как");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Внимание", "Невозможно сохранить файл: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_ins_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_cut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_copy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_povt_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_otm_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_action_13_triggered()
{
        bool fontSelected;
        QFont font = QFontDialog::getFont(&fontSelected, this);
        if (fontSelected)
            ui->textEdit->setFont(font);

}

void MainWindow::on_action_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_action_14_triggered()
{
    QMessageBox::about(this,"О программе","Текстовый редактор\n Додонов Александр Дмитриевич\nБ16-511");

}
