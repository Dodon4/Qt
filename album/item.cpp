#include "item.h"
#include <QList>
#include <QDataStream>
#include <QDebug>
#include <QPixmap>
#include <QTime>

Item::Item()
{
    qDebug()<<"create item"<<this;
    m_parent=nullptr;
    m_name=QString("Новый ");
}

Item::Item(QString name)
{
    qDebug()<<"crezte item"<<this<<name;
    m_parent=nullptr;
    m_name=name;
    m_comment=QString("nj");
}

Item::~Item()
{
    qDebug()<<"destroy item"<<this<<"name"<<m_name;
    setParent(nullptr);
    for(auto ch:m_children)
    {
        if(ch)
            delete ch;
    }
    m_children.clear();
}

void Item::setParent(Item *p)
{
    if(p==m_parent)
         return;
    if(p)
    {
        qDebug()<<"set parent"<<p<<p->name()<<"to"<<this<<m_name;
        if(m_parent)
        {
            m_parent->takeChild(m_parent->indexOf(this));
        }
        m_parent=p;
        m_parent->insertChild(this);
    }
}

void Item::insertChild(Item *p, int position)
{
    if(!p)
        return;
    qDebug()<<"insert child Item"<<p->name()<<"to item"<<m_name<<"at"<<position;
    if(m_children.contains(p))
        p->setParent(this);
    else
    {
        if(position<0||position>m_children.size())
            m_children.insert(m_children.size(),p);
        else
            m_children.insert(position,p);

        p->setParent(this);
    }
}

Item *Item::takeChild(int  i)
{
    Item *p=m_children.takeAt(i);
    if(p)
        p->setParent(nullptr);
    qDebug()<<"take child Item at"<<i<<p<<p->name()<<"from Item"<<this<<m_name;
    return p;
}

Item *Item::childAt(int i) const
{
    if(i<0||i>=m_children.size())
        return nullptr;
    Item *p=m_children.at(i);
    qDebug()<<"ch"<<i<<p<<"parent iten";
    return p;
}

int Item::indexOf(Item *p) const
{
    return m_children.indexOf(p);
}

int Item::childCount() const
{
    return m_children.size();
}

QString Item::name() const
{
    return m_name;
}

void Item::setName(const QString name)
{
    m_name=name;
}

QString Item::comment() const
{
    return m_comment;
}

void Item::setcomment(const QString name)
{
    m_comment=name;
}

QDataStream& operator<<(QDataStream &stream, const Artist &artist)
{
    stream <<artist.name()<<artist.comment()<<artist.photo()<<artist.country();
    int alb=artist.childCount();
    stream << alb;
    for(int i=0;i<alb;i++)
    {
        Album const *album = artist.childAt(i)->toAlbum();
        if(album)
            stream<<*album;
    }
     return stream;
}

QDataStream& operator>>(QDataStream &stream, Artist &artist)
{
    QString name;
    QPixmap photo;
    QString comment;
    QString country;
    int count;
    Album *alb;
    stream>>name>>comment>>photo>>country ;
    artist.setName(name);
    artist.setCountry(country);
    artist.setPhoto(photo);
    artist.setcomment(comment);
    stream>>count;
    for (int i =0; i<count; i++)
    {
        alb = new Album();
        stream>>*alb;
        artist.insertChild(alb,i);
    }
    return stream;
}

QDataStream &operator<<(QDataStream &stream, const Album &album)
{
    stream<<album.name()<<album.comment()<<album.year()<<album.genre()<<album.cover();
    int alb=album.childCount();
    stream<<alb;

    for(int i=0; i < alb; i++)
    {
        Song const *song = album.childAt(i)->toSong();
        if (song)
            stream<<*song;
    }
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Album &album)
{
    QString name;
    QPixmap cover;
    QString genre;
    QString comment;
    int year;
    int count;
    Song *son;
    stream>>name>>comment>>year>>genre>>cover;
    album.setName(name);
    album.setcomment(comment);
    album.setYear(year);
    album.setGenre(genre);
    album.setCover(cover);
    stream>>count;
    for (int i =0; i<count; i++)
    {
        son = new Song();
        stream >> *son;
        album.insertChild(son, i);
    }
    return stream;
}

QDataStream &operator<<(QDataStream &stream, const Song &song)
{
    stream<<song.name()<<song.rating()<<song.tim()<< song.comment();

    return stream;
}

QDataStream &operator>>(QDataStream &stream, Song &song)
{
    QString name;
    QString comment;
    int rate;
    QTime t;
    stream>>name>>rate>>t>>comment;
    song.setName(name);
    song.setcomment(comment);
    song.setRating(rate);
    song.setTime(t);
    return stream;
}

void Artist::setPhoto(const QPixmap f)
{
    m_photo=f;
}

QPixmap Artist::photo() const
{
    return m_photo;
}

void Artist::setCountry(const QString c)
{
    m_country=c;
}

QString Artist::country() const
{
    return m_country;
}

void Album::setYear(const int y)
{
    m_year=y;
}

int Album::year() const
{
    return m_year;
}

void Album::setGenre(const QString g)
{
    m_genre=g;
}

QString Album::genre() const
{
    return m_genre;
}

void Album::setCover(const QPixmap c)
{
    m_cover=c;
}

QPixmap Album::cover() const
{
    return m_cover;
}

void Song::setRating(const int r)
{
    m_rating=r;
}

int Song::rating() const
{
    return m_rating;
}

void Song::setTime(const QTime t)
{
    m_time=t;
}

QTime Song::tim() const
{
    return m_time;
}

QDataStream& operator << (QDataStream &stream, Item &root)
{
    int count = root.childCount();
    stream << count;
    for(int i=0; i<count; ++i)
    {
        Artist *artist = root.childAt(i)->toArtist();
        if(artist)
            stream << *artist;
    }
    return stream;
}

Item *Item::parent()
{
    return m_parent;
}
