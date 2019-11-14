#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMutex>
#include "staticvar.h"
#include "producer.h"
#include "consumer.h"


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


void MainWindow::on_find_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("Text Files (*.txt)"));
    setWindowTitle(fileName);
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    DataSize = file.size();

    ui->filePath->setText(fileName);
    ui->File1->setText(file.readAll());
    file.close();
}

void MainWindow::on_start_clicked()
{
    Producer *producer = new Producer(this);
    Consumer *consumer = new Consumer(this);

    connect(consumer, SIGNAL(ConsumerUpdate(const QString &, char, int)),this, SLOT(consumerUpdateBuffer(const QString &, char, int)));
    connect(producer, SIGNAL(ProducerUpdate(const QString &)),this, SLOT(producerUpdateBuffer(const QString &)));

    producer->start();
    consumer->start();
}

void MainWindow::producerUpdateBuffer(const QString &text)
{
  ui->buffer->setText(text);
}

void MainWindow::consumerUpdateBuffer(const QString &text, char sim, int cycle_count)
{
    QString tmp = (ui->File2->toPlainText());
       tmp.append(sim);
       ui->File2->setText(tmp);
       ui->buffer->setText(text);
       ui->CyclesCount->setText(QString::number(cycle_count));
}


void Producer::run()
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    for (int i=0; i<DataSize; ++i)
    {
        mutex.lock();
        if (RecordedCells == BufferSize)
            bufferNotFull.wait(&mutex);
        mutex.unlock();

        QObject().thread()->usleep(1000*25*1);
        file.read(&(buffer[i % 100]),1);
        emit ProducerUpdate(QString(buffer));
        mutex.lock();
        ++RecordedCells;
        bufferNotEmpty.wakeAll();
        mutex.unlock();
    }

    file.close();
}


void Consumer::run()
{
    QFile file("file2.txt");
    file.open(QIODevice::WriteOnly);

    for (int i=0; i<DataSize; ++i)
    {
        if(i%100 == 0)
            CycleCount++;

        mutex.lock();
        if (RecordedCells == 0)
            bufferNotEmpty.wait(&mutex);
        mutex.unlock();

        file.write(&(buffer[i % BufferSize]));
        emit ConsumerUpdate(QString(buffer), (buffer[i % BufferSize]), CycleCount);

        mutex.lock();
        --RecordedCells;
        bufferNotFull.wakeAll();
        mutex.unlock();
    }

    file.close();
}
