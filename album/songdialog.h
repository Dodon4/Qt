#ifndef SONGDIALOG_H
#define SONGDIALOG_H

#include <QDialog>
#include<QDataWidgetMapper>
#include"musicmodel.h"
namespace Ui {
class SongDialog;
}

class SongDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SongDialog(QWidget *parent = nullptr);
    ~SongDialog();
    void setModel(MusicModel *);
    void setModelIndex(const QModelIndex &);
    void accept();
    bool addSong(MusicModel *model,const QModelIndex &parent);

private:
    Ui::SongDialog *ui;
    QDataWidgetMapper m_mapper;
};

#endif // SONGDIALOG_H
