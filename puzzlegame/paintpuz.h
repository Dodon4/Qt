#ifndef PAINTPUZ_H
#define PAINTPUZ_H

#include <QPixmap>

#include <QtGlobal>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPainter>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QHash>
#include <QDebug>
#include <QMessageBox>
#include <QSet>
#define PIECE_SIZE 50

enum ConnectorPosition{None,Out,In};
class paintpuz : public QGraphicsPathItem
{   // Q_OBJECT
    Q_PROPERTY(QPixmap image READ pixmap WRITE setPixmap)
    Q_PROPERTY(QPixmap coordinates READ coord WRITE setCoord)
    ConnectorPosition connector_position[4];

public:
    enum Direction {North,East,South,West};
    paintpuz();
    paintpuz(ConnectorPosition n,ConnectorPosition e,ConnectorPosition s,ConnectorPosition w);
    paintpuz* m_neighbors[4];
    void constructShape(QPainterPath& shape);
    QPixmap pixmap() const;
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    void paint(QPainter * p, const QStyleOptionGraphicsItem * option, QWidget * widget);
    QPoint coord() const;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void checkNeighbors(QSet<QPoint> &checked);
    void findneighbor(Direction d);
    qreal size;
    int puzzle_item_count;

private:
public slots:

    void link(paintpuz *piece,Direction direction);
    void setPixmap(QPixmap image);
    void setCoord(QPoint coordinates);

    QPixmap m_image;
    QPoint m_coordinates;

};
inline uint qHash (const QPoint &key,uint seed)
{
return qHash(key.x(),seed)*key.y();}
#endif
