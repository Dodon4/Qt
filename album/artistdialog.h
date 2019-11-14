#ifndef ARTISTDIALOG_H
#define ARTISTDIALOG_H

#include <QDialog>
#include<QDataWidgetMapper>
#include"musicmodel.h"
namespace Ui {
class ArtistDialog;
}

class ArtistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArtistDialog(QWidget *parent = nullptr);
    ~ArtistDialog();
    void setModel(MusicModel *);
    void setModelIndex(const QModelIndex &);
    void accept();
    bool addArtist(MusicModel *model,const QModelIndex &parent);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ArtistDialog *ui;
    QString fileName;
    QDataWidgetMapper m_mapper;
};

#endif // ARTISTDIALOG_H
