#include "mainwindow.h"
#include <QApplication>
#include "item.h"
#include<QTreeView>
#include"ratingdelegate.h"
#include"albumdialog.h"
#include"artistdialog.h"
#include"songdialog.h"
int main(int argc, char *argv[])
{
 QApplication a(argc, argv);
 MainWindow w;
 w.show();
 return a.exec();
}
