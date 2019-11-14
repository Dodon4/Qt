#ifndef ITEM_H
#define ITEM_H
#include<QList>
#include<QString>
#include<QObject>
#include<QPixmap>
#include<QDataStream>
#include<QTime>
class Artist;
class Album;
class Song;

class Item
{
public:
    Item();
    Item(QString name);
    virtual ~Item();
    Item * parent();
    void setParent(Item *);
    void insertChild(Item *, int position=-1);
    Item *takeChild(int );
    Item *childAt(int) const;
    int indexOf(Item*)const;
    int childCount()const;
    QString name() const;
    void setName(const QString name);
    QString comment() const;
    void setcomment(const QString name);
    virtual Artist* toArtist(){return nullptr;}
    virtual Album* toAlbum(){return nullptr;}
    virtual Song* toSong(){return nullptr;}

private:
    Item* m_parent;
    QList<Item*>m_children;
    QString m_name;
    QString m_comment;
};

class Artist:public Item
{
private:
    QPixmap m_photo;
    QString m_country;
public:
    Artist():Item(){}
    Artist(QString name):Item(name){}
    void setPhoto(const QPixmap f);
    QPixmap photo() const;
    void setCountry(const QString c);
    QString country() const;
    virtual Artist * toArtist(){return this;}
    virtual Album * toAlbum(){return nullptr;}
    virtual Song * toSong(){return nullptr;}
};

class Album:public Item
{
private:
    int m_year;
    QPixmap m_cover;
    QString m_genre;
public:
    Album():Item(){}
    Album(QString name):Item(name){}
    void setYear(const int y);
    int year()const;
    void setGenre(const QString g);
    QString genre()const;
    void setCover(const QPixmap c);
    QPixmap cover() const;
    virtual Artist * toArtist(){return nullptr;}
    virtual Album * toAlbum(){return this;}
    virtual Song * toSong(){return nullptr;}
};

class Song:public Item
{
private:
   QTime m_time;
   int m_rating;
public:
    void setRating(const int r);
    int rating()const;
    void setTime(const QTime t);
    QTime tim()const;
    Song():Item(){}
    Song(QString name):Item(name){}
    virtual Artist * toArtist(){return nullptr;}
    virtual Album * toAlbum(){return nullptr;}
    virtual Song * toSong(){return this;}
};
QDataStream& operator << (QDataStream &stream, Item &root);
QDataStream& operator<< (QDataStream &stream, Item &root);
QDataStream& operator<<(QDataStream& stream, const  Artist& artist);
QDataStream& operator>>(QDataStream& stream,  Artist& artist);
QDataStream& operator<<(QDataStream& stream,  const Album& album);
QDataStream& operator>>(QDataStream& stream,  Album& album);
QDataStream& operator<<(QDataStream& stream, const Song& song);
QDataStream& operator>>(QDataStream& stream,  Song& song);

#endif // ITEM_H
