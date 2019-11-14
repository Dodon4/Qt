#include "mainwindow.h"
#include <QApplication>
#include<QCommandLineParser>
#include"udpchat.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCommandLineParser parser;

    QCommandLineOption portOption(QStringList()<<"p"<<"port",".");
    parser.addOption(portOption);
    QCommandLineOption nameOption(QStringList()<<"n"<<"nickname",".");
    parser.addOption(nameOption);
    parser.process(app);
    qDebug()<<parser.isSet(portOption)<<parser.positionalArguments();

    QStringList args= parser.positionalArguments();
    if (!parser.isSet(portOption)) {
        args.insert(args.end(), "255555");
    }
    if (!parser.isSet(nameOption)) {
        args.insert(args.begin(), "dodon");
    }
    udpchat chat(args.at(0));
    chat.setWindowTitle(QString("easy talk[%1@%2]").arg(args.at(0)).arg(args.at(1)));
    chat.startNetworking(args.at(1).toUInt());
    chat.show();



    MainWindow w;

    return app.exec();
}