#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_3->setEnabled(false);
    connect(&process,SIGNAL(finished(int)),this,SLOT(get_lineEdit_3()));
    connect(&process,SIGNAL(finished(int)),this,SLOT(get_lineEdit_4()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    filename = QFileDialog::getOpenFileName(this, QString("Open"),QDir::currentPath(),"Program files (*.app)");
    ui->lineEdit->setText(filename);
    ui->lineEdit->textChanged(filename);
    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(show_label_1()));

}

void MainWindow::on_pushButton_2_clicked()
{
    time.start();
    QString argStr = ui->lineEdit_2->text();
    arguments = argStr.split(" ");
    arguments.count() != 0 ? process.start(filename,arguments) : process.start(filename);
    process.start(filename,arguments);
    ui->pushButton_3->setEnabled(true);
}

void MainWindow::on_pushButton_3_clicked()
{
    process.terminate();
    ui->pushButton_3->setEnabled(false);

}

void MainWindow::show_label_1()
{
    QByteArray out = process.readAll();
    QTextCodec *codec = QTextCodec::codecForName("KOI8-R");
    QString string = codec->toUnicode(process.readAll());
    ui->ChildOutput->append(string);
}


void MainWindow::get_lineEdit_4()
{
    int code = process.exitCode();
    ui->lineEdit_4->setText(QString::number(code));
}

void MainWindow::get_lineEdit_3()
{
    int duration = time.elapsed();
    ui->lineEdit_3->setText(QString::number(duration/1000));
}
