#ifndef ALBUMDIALOG_H
#define ALBUMDIALOG_H

#include <QDialog>
#include<QString>
#include"musicmodel.h"
#include<QDataWidgetMapper>
namespace Ui {
class AlbumDialog;
}

class AlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlbumDialog(QWidget *parent = nullptr);
    ~AlbumDialog();
    void setModel(MusicModel *model);
    void setModelIndex(const QModelIndex &model);
    void accept();
    bool addAlbum(MusicModel *model,const QModelIndex &parent);

private slots:
    void on_pushButton_clicked();

private:
    Ui::AlbumDialog *ui;
    QString fileName;
    QDataWidgetMapper m_mapper;
};

#endif // ALBUMDIALOG_H
