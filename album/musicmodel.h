#ifndef MUSICMODEL_H
#define MUSICMODEL_H
#include<QAbstractItemModel>
#include"item.h"
#include <QModelIndex>
#include <QTime>
#include<QVariant>
#include<QObject>
#include<QMetaObject>

class MusicModel : public QAbstractItemModel
{

private:

public:
    MusicModel();
    QModelIndex index(int row,int column,const QModelIndex &parent) const ;
    QModelIndex parent(const QModelIndex &ch) const;
    int columnCount(const QModelIndex &parent)const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index)const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    bool insertRows(int row, int count,const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count,const QModelIndex &parent = QModelIndex());
    QVariant headerData(int section,Qt::Orientation orientation,int role=Qt::DisplayRole) const;
    Item *m_root;

};
QDataStream& operator<< (QDataStream &stream, Item &root);
QDataStream& operator>> (QDataStream &stream, Item &root);

#endif // MUSICMODEL_H
