#ifndef CONSUMER_H
#define CONSUMER_H
#include <QThread>
#include "mainwindow.h"

class Consumer : public QThread
{
    Q_OBJECT

public:

    MainWindow *form;
    Consumer(MainWindow *f, QObject *parent = NULL) : QThread(parent), form(f) {}
    void run() override;

signals:
    void ConsumerUpdate(const QString &text, char sim, int cycleCount);
};


#endif // CONSUMER_H
