#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "puzzle.h"
#include <QFileDialog>
#include <QDir>
#include <QLabel>
#include <QMessageBox>
#include <QGraphicsScene>
#include "game.h"
#include <QGraphicsView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setName(QString fileName)
{
    this->fileName=fileName;
}

void MainWindow::on_pushButton_3_clicked()
{
        fileName = QFileDialog::getOpenFileName(this,
       tr("Open Image"), QDir::homePath(), tr("Image Files (*.png *.jpg *.bmp)"));

    ui->frame->setPrev(fileName);


    ui->fileName->setText(fileName);
    QPixmap pix(fileName);
    ui->frame->setPrev(fileName);
    vs = new QPixmap(fileName);
    }
QString MainWindow::imgName()
{
    return fileName;
}

void MainWindow::setScene(/*QSize size, */game* newScene, QGraphicsView* view)
{
this->scene = newScene;
this->view = view;
}
void MainWindow::on_pushButton_clicked()
{

    if (vs) {
     QGraphicsView gv;
     scene->setup(ui->frame->Value(), vs->scaled(50*(ui->frame->Value().width()), 50*(ui->frame->Value().height())));
     view->show();
     this->close();
    } else {
    QMessageBox box;
    box.setText("Изображение не выбрано");
    box.show();
    box.exec();

    }

}

void MainWindow::on_pushButton_2_clicked()
{
        this->close();
}
