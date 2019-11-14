#ifndef PRODUCER_H
#define PRODUCER_H

#include <QThread>
#include "mainwindow.h"


class Producer : public QThread
{
    Q_OBJECT

public:
    MainWindow *form;
    Producer(MainWindow *f, QObject *parent = NULL) : QThread(parent), form(f) {}
    void run() override;

signals:
    void ProducerUpdate(const QString &text);
};


#endif // PRODUCER_H
