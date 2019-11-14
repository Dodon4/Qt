#include "musicmodel.h"
#include "item.h"
#include<QObject>
#include<QDebug>
MusicModel::MusicModel()
{
    m_root=new Item;
}
QModelIndex MusicModel::index(int row, int column, const QModelIndex &parent) const
{
    Item *parentItem=m_root;
    if(parent.isValid())
        parentItem=static_cast<Item*>(parent.internalPointer());
    if(parentItem->childCount()>row)
        if(parentItem->childAt(row))
        {
            return createIndex(row, column, parentItem->childAt(row));
        }
    return QModelIndex();
}

QModelIndex MusicModel::parent(const QModelIndex &ch) const
{
    if(!ch.isValid())
        return QModelIndex();
    Item *chItem;
    chItem=static_cast<Item*>(ch.internalPointer());
    if(chItem==m_root)
        return QModelIndex();
    if(chItem->parent()==m_root)
        return QModelIndex();
    if(!chItem->parent())
        return QModelIndex();
    Item *parent = chItem->parent();
    if(!parent->parent()) return QModelIndex();
    else
    {
        Item *grandparent = parent->parent();
        return createIndex(grandparent->indexOf(parent),0,parent);
    }
}

int MusicModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

int MusicModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        Item *tr;
        tr=static_cast<Item*>(parent.internalPointer());
        return tr->childCount();
    }
    return m_root->childCount();
}

QVariant MusicModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
        case Qt::DisplayRole:
        {
            if(index.isValid())
            {
                Item *item=static_cast<Item*>(index.internalPointer());
                int c=index.column();
                switch(c)
                {
                 case 0:
                {
                    return item->name();
                }
                case 1:
                {
                    if(item->toSong())
                        return item->toSong()->tim();
                    break;
                }
                case 2:
                {
                    if(item->toSong())
                        return item->toSong()->rating();
                    break;
                }
                case 3:
                {
                     if(item->toSong())
                         return item->toSong()->comment();
                     break;
                }
                default: return QVariant();
                }
            }
        break;
        }
    case Qt::EditRole:
    {
        if(index.isValid())
        {
            int coloumn = index.column();
            Item *item = static_cast<Item*>(index.internalPointer());
            if(item)
            {
                switch (coloumn)
                {
                case 0:
                    return item->name();
                case 1:
                    if(item->toSong()) return item->toSong()->tim();
                    if(item->toAlbum()) return item->toAlbum()->genre();
                    if(item->toArtist()) return item->toArtist()->country();
                    break;
                case 2:
                    if(item->toSong()) return item->toSong()->rating();
                    if(item->toAlbum()) return item->toAlbum()->year();
                    if(item->toArtist()) return item->comment();
                    break;
                case 3:
                     if(item->toSong()) return item->comment();
                     if(item->toAlbum()) return item->comment();
                     if(item->toArtist()) return item->toArtist()->photo();
                    break;
                case 4:
                    if(item->toAlbum()) return item->toAlbum()->cover();
                    break;
                }
            }
            else return QVariant();
        }
        else return QVariant();
        break;
    }
    default:break;
    }
    return QVariant();
}

Qt::ItemFlags MusicModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool MusicModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;
    if(role!=Qt::EditRole&&role!=Qt::DisplayRole)
        return false;
    Item * item = static_cast<Item *>(index.internalPointer());
    if (item)
    {
        switch (index.column())
        {
            case 0:
            {
                item->setName(value.toString());
                break;
            }
            case 1:
            {
                if (item->toArtist())
                    item->toArtist()->setCountry(value.toString());
                if (item->toAlbum())
                    item->toAlbum()->setGenre(value.toString());
                if (item->toSong())
                {
                    QTime tim = QTime::fromString( value.toString(), Qt::ISODate );
                    item->toSong()->setTime(tim);
                }
                break;
            }
            case 2:
            {
                if (item->toSong())
                    item->toSong()->setRating(value.toInt());
                if (item->toAlbum())
                    item->toAlbum()->setYear(value.toInt());
                if (item->toArtist())
                    item->toArtist()->setcomment(value.toString());
                break;
            }
            case 3:
            {
                if (item->toAlbum())
                    item->toAlbum()->setcomment(value.toString());
                if (item->toSong())
                    item->setcomment(value.toString());
                if (item->toArtist())
                    item->toArtist()->setPhoto(value.value<QPixmap>());
                break;
            }
            case 4:
            {
                if (item->toAlbum())
                    item->toAlbum()->setCover(value.value<QPixmap>());
                break;
            }
        }
        qDebug()<<"change text";
        emit dataChanged(index, index);
        return true;
 }
    return false;
}

bool MusicModel::insertRows(int row,int count, const QModelIndex &parent)
{
    Item *parentItem;
    if(parent.isValid())
    {
        parentItem = static_cast<Item *>(parent.internalPointer());
    }
    else
        parentItem=m_root;
    for ( int i = row; i <= (row + count - 1); i++ )
    {
        Item *newitem;
        if(parentItem==m_root)
            newitem=new Artist();
        if(parentItem->toArtist())
            newitem=new Album();
        if(parentItem->toAlbum())
            newitem=new Song();
        beginInsertRows(parent, row, row+count-1);
        parentItem->insertChild(newitem,i);
        endInsertRows();
    }
    return true;
}

bool MusicModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Item *parentItem;
    if(parent.isValid())
    {
        parentItem = static_cast<Item *>(parent.internalPointer());
    }
    else
        parentItem=m_root;
    for ( int i = row; i <= (row + count - 1); i++ )
    {
        Item *b;
        beginRemoveRows(parent, row, row);
        b= parentItem->takeChild(i);
        endRemoveRows();
        delete b;
        return true;
    }
    return true;
}

QVariant MusicModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();
    switch(section)
    {
    case 0:
        return QVariant("Название");
    case 1:
        return QVariant("Длительность");
    case 2:
        return QVariant("Рейтинг");
    case 3:
        return QVariant("Комментарий");
    default:
        return QVariant();
    }
}

QDataStream &operator>>(QDataStream &stream, Item &root)
{
    int artist_count;
    Artist *art;
    stream >> artist_count;
    for (int i =0; i<artist_count; i++)
    {
        art = new Artist();
        stream >> *art;
        root.insertChild(art,i);
    }
    return stream;
}

