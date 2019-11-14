#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include "QVector"
#include "QColor"
#include "QRgb"
#include "QThreadPool"
#include "QDebug"
#include "QtConcurrent/QtConcurrent"
#include "QThread"
#include "QLocale"


Res mapfunc(Task tasks)
{
    QList<Res> ex;
    QList<int> red;
    QList<int> green;
    QList<int> blue;
    for(int i = tasks.x - tasks.msize/2; i< (tasks.x + tasks.msize/2); i++)
    {
        for( int j = tasks.y - tasks.msize/2; j < (tasks.y + tasks.msize/2); j++)
        {
            red.append(QColor(tasks.imgfrom->pixel(i, j)).red());
            green.append(QColor(tasks.imgfrom->pixel(i, j)).green());
            blue.append(QColor(tasks.imgfrom->pixel(i, j)).blue());
        }
    }
    qSort(red.begin(), red.end());
    qSort(green.begin(), green.end());
    qSort(blue.begin(), blue.end());
    QColor rescolor(red.at((tasks.msize*tasks.msize-1)/2),green.at((tasks.msize*tasks.msize-1)/2),blue.at((tasks.msize*tasks.msize-1)/2));
    return Res{tasks.x-tasks.msize/2, tasks.y-tasks.msize/2, rescolor, tasks.imgto};
}

void reducefunc(QImage &result,const Res res)
{
   res.imgto->setPixel(res._x, res._y, res.color.rgb() );
}
void MainWindow::on_pushButton_4_clicked()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("Save image file"),QApplication::applicationDirPath(),tr("Images (*.png *.jpg)"));
    if(!fn.isEmpty() && !fn.isNull())
    {
            resimg->save(fn);
    }

}

void MainWindow::on_actionRUS_triggered()
{
    transl.load(QString("filter_")+QString("ru_RU"));
    qApp->installTranslator(&transl);
}

void MainWindow::on_actionEN_triggered()
{
    transl.load(QString("filter_")+QString("en_EN"));
    qApp->installTranslator(&transl);
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        ui->lineEdit_5->setText(QString::number(thnum));
    }
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage *image = new QImage(":/default.jpg");

    ui->label->setPixmap(QPixmap::fromImage(*image));
    ui->label_2->setPixmap(QPixmap::fromImage(*image));
    ui->lineEdit_5->setText(QString::number(thnum));
    img = image;
    resimg = new QImage(image->copy(0,0,image->width(),image->height()));
    msize = 5;
    thnum = QThread::idealThreadCount();

    QThreadPool::globalInstance()->setMaxThreadCount(thnum);
    ui->pushButton_4->setEnabled(false);
    transl.load(QString("filter_") + QLocale::system().name());
    qApp->installTranslator(&transl);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage* MainWindow::getResImg()
{
    return resimg;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
    {
        QImage *image = new QImage(fileName);
        filename = fileName;
        ui->label->setPixmap(QPixmap::fromImage(*image));
        ui->lineEdit->setText(filename);
        img = image;
        delete resimg;
        resimg =  new QImage(image->copy(0,0,image->width(),image->height()));
    }
    ui->pushButton_4->setEnabled(false);
    return;
}




void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    msize = arg1.toInt();
}

void MainWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
    thnum = arg1.toInt();
    QThreadPool::globalInstance()->setMaxThreadCount(thnum);
}

void MainWindow::on_pushButton_clicked()
{
    int wcount = msize/2;
    int hcount = msize/2;

    int x,y,z,i,j;
    QImage *buf_img = new QImage(img->width()+(2*msize+1)/2, img->height()+(2*msize+1)/2, QImage::Format_RGB32);

    for(x=0; x<msize/2; x++)
    {
        for(y=0; y<msize/2; y++)
        {
            buf_img->setPixel(x,y,QColor(img->pixel(x,y)).rgb());
        }
    }
    for(x=img->width(); x<img->width()+msize/2; x++)
    {
        for(y=0; y<msize/2; y++)
        {
            buf_img->setPixel(x+msize/2,y,QColor(img->pixel(x-msize/2,y)).rgb());
        }
    }
    for(x=img->width(); x<img->width()+msize/2; x++)
    {
        for(y=img->height(); y<img->height()+msize/2; y++)
        {
            buf_img->setPixel(x+msize/2,y+msize/2,QColor(img->pixel(x-msize/2,y-msize/2)).rgb());
        }
    }
    for(x=0; x<msize/2; x++)
    {
        for(y=img->height(); y<img->height()+msize/2; y++)
        {
            buf_img->setPixel(x,y+msize/2,QColor(img->pixel(x,y-msize/2)).rgb());
        }
    }
    for(x=0; x<img->width(); x++)
    {
        for(y=0; y<msize/2; y++)
        {
            buf_img->setPixel(x+msize/2,y,QColor(img->pixel(x,y)).rgb());
        }
    }
    for(x=img->width(); x<img->width()+msize/2; x++)
    {
        for(y=0; y<img->height(); y++)
        {
            buf_img->setPixel(x+msize/2,y+msize/2,QColor(img->pixel(x-msize/2,y)).rgb());
        }
    }
    for(x=0; x<img->width(); x++)
    {
        for(y=img->height(); y<img->height()+msize/2; y++)
        {
            buf_img->setPixel(x+msize/2,y+msize/2,QColor(img->pixel(x,y-msize/2)).rgb());
        }
    }
    for(x=0; x<msize/2; x++)
    {
        for(y=0; y<img->height(); y++)
        {
            buf_img->setPixel(x,y+msize/2,QColor(img->pixel(x,y)).rgb());
        }
    }
    for(x=0; x<img->width(); x++)
    {
        for(y=0; y<img->height(); y++)
        {
            buf_img->setPixel(x+msize/2,y+msize/2,QColor(img->pixel(x,y)).rgb());
        }
    }

    QList<Task> tasks;

    QImage *rimg = new QImage(img->copy(msize/2, msize/2,img->width(), img->height()));


    for(wcount = msize/2; wcount<buf_img->width()- msize/2; wcount++)
    {
        for(hcount = msize/2; hcount<buf_img->height()- msize/2; hcount++)
        {
            tasks.append(Task{buf_img, wcount, hcount ,msize, rimg});
        }
    }

    int tmph = 0;
    int addh = img->height()/thnum+1;

    ui->lineEdit->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_5->setEnabled(false);
    ui->pushButton_4->setEnabled(false);



    QFutureWatcher<QImage> watcher;
    QFuture<QImage> res = QtConcurrent::mappedReduced(tasks,mapfunc,reducefunc);

    connect(ui->pushButton_3, SIGNAL(clicked(bool)), &watcher, SLOT(cancel()));
    watcher.setFuture(res);

    while (!watcher.isFinished())
    {
        if(watcher.isCanceled())
        {
            watcher.cancel();
            ui->lineEdit->setEnabled(true);
            ui->lineEdit_3->setEnabled(true);
            ui->lineEdit_5->setEnabled(true);
            ui->progressBar->setValue(0);
            ui->label_9->setText(QString::number(0));
            return;
        }
        ui->progressBar->setValue(100*watcher.progressValue()/watcher.progressMaximum());
        ui->label_9->setText(QString::number(watcher.progressValue()));
        QApplication::processEvents();
    }

    QImage tmp = res.result();
    ui->label_2->setPixmap(QPixmap::fromImage(*rimg));
    resimg = rimg;

    ui->lineEdit->setEnabled(true);
    ui->lineEdit_3->setEnabled(true);
    ui->lineEdit_5->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
}
