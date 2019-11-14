#include "paintpuz.h"
#include<QPainter>
#include<QPainterPath>
#include<QPixmap>
#include <QGraphicsPixmapItem>
#include <QVariant>
paintpuz::paintpuz()
{
            connector_position[North]=connector_position[South]=connector_position[East]=connector_position[West]=None;
            size=PIECE_SIZE;
            QPainterPath shape;
            shape.addRect(-1*size/2.,-1*size/2.,size/2,size/2);
            shape.closeSubpath();
            m_coordinates=QPoint(0,0);
            m_neighbors[0]=m_neighbors[1]=m_neighbors[2]=m_neighbors[3]=0;
            puzzle_item_count=0;
            setPath(shape);
}

paintpuz::paintpuz(ConnectorPosition n,
ConnectorPosition e,
ConnectorPosition s,
ConnectorPosition w)
{
        size=PIECE_SIZE;
        connector_position[North]=n;
        connector_position[East]=e;
        connector_position[South]=s;
        connector_position[West]=w;
        QPainterPath sh;
        constructShape(sh);
        setPath(sh);
        m_coordinates=QPoint(0,0);
        m_neighbors[0]=m_neighbors[1]=m_neighbors[2]=m_neighbors[3]=0;
        puzzle_item_count=0;
    }

    QPixmap paintpuz::pixmap() const
    {
        return m_image;

}
void paintpuz::constructShape(QPainterPath &shape)
{
    shape.moveTo(-1*size/2.,-1*size/2.);
    shape.lineTo(-1*size/4.,-1*size/2.);
    connector_position[North] == Out ? shape.arcTo(-1*size/4., -3*size/4., size/2., size/2., 180., -180.) : connector_position[North] == In ? shape.arcTo(-1*size/4., -3*size/4., size/2., size/2., 180., 180.) : shape.lineTo(size/4., -1*size/2.);
    shape.lineTo(size/2., -1*size/2.);

    shape.lineTo(size/2.,-1*size/4.);
    connector_position[East] == Out ? shape.arcTo(size/4., -1*size/4., size/2., size/2., 90., -180.) : connector_position[East] == In ? shape.arcTo(size/4., -1*size/4., size/2., size/2., 90., 180.) : shape.lineTo(size/2., size/4.);
    shape.lineTo(size/2., size/2.);

    shape.lineTo(size/4.,size/2.);
    connector_position[South] == Out ? shape.arcTo(-1*size/4., size/4., size/2., size/2., 0., -180.) : connector_position[South] == In ? shape.arcTo(-1*size/4., size/4., size/2., size/2., 0., 180.) : shape.lineTo(-1*size/4., size/2.);
    shape.lineTo(-1*size/2., size/2.);

    shape.lineTo(-1*size/2.,size/4.);
    connector_position[West] == Out ? shape.arcTo(-3*size/4., -1*size/4., size/2., size/2., 270., -180.) : connector_position[West] == In ? shape.arcTo(-3*size/4., -1*size/4., size/2., size/2., 270., 180.) : shape.lineTo(-1*size/2., -1*size/4.);
    shape.lineTo(-1*size/2., -1*size/2.);
    shape.closeSubpath();
}


void paintpuz::paint(QPainter * p, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
        p->setClipPath(path());
        QRect rect=boundingRect().toRect();
        p->drawPixmap(rect.x(),rect.y(),m_image);
        p->setPen(Qt::black);
        p->drawPath(path());
}
void paintpuz::setCoord(QPoint coordinates)
{
    m_coordinates = coordinates;
}
void paintpuz::link(paintpuz *p, Direction d)
{
        if(!m_neighbors[d]){
            qDebug()<<coord()<<"linked to"<<p->coord();
            m_neighbors[d]=p;
            p->itemChange(ItemPositionHasChanged,QVariant(p->pos()));
            p->link(this,(Direction)((int)d+2>3 ? (int)d-2 : (int)d+2));
        }
}
QPoint paintpuz::coord() const {
     return m_coordinates;
}
void paintpuz::setPixmap(QPixmap image)
{
        m_image=image;
        update(-1*size/2.,-1*size/2.,size,size);
}

QVariant paintpuz::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged && scene())
    {
        QPointF newP = value.toPointF();
        QPointF nei;
        if (m_neighbors[North])
        {
            nei = QPointF(newP.x(), newP.y() - PIECE_SIZE);
            if (m_neighbors[North]->pos() != nei) m_neighbors[North]->setPos(nei);
            //if (m_neighbours[East]->pos() != nei) m_neighbours[East]->setPos(nei);
        }
        if (m_neighbors[South])
        {
            nei = QPointF(newP.x(), newP.y() + PIECE_SIZE);
            if (m_neighbors[South]->pos() != nei) m_neighbors[South]->setPos(nei);
        }
         if (m_neighbors[East])
         {
         nei = QPointF(newP.x() + PIECE_SIZE, newP.y());
         if (m_neighbors[East]->pos() != nei) m_neighbors[East]->setPos(nei);
         }
        if (m_neighbors[West])
        {
            nei = QPointF(newP.x() - PIECE_SIZE, newP.y());
            if (m_neighbors[West]->pos() != nei) m_neighbors[West]->setPos(nei);
        }
    }
    //

    return QGraphicsItem::itemChange(change, value);
}
void paintpuz::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

        QSet<QPoint> neigbors;
        checkNeighbors(neigbors);
        if(neigbors.count() == puzzle_item_count)
        {
            QMessageBox::information(0,"Congratulations!","<h2>You won!</h2>");
            exit(0);
        }

        QGraphicsPathItem::mouseReleaseEvent(event);
}
void paintpuz::checkNeighbors(QSet<QPoint> &checked){
        if(checked.contains(coord()))
        return;
        checked.insert(coord());
        findneighbor(North);
        findneighbor(East);
        findneighbor(South);
        findneighbor(West);

        if(m_neighbors[North])
        m_neighbors[North]->checkNeighbors(checked);
        if(m_neighbors[East])
        m_neighbors[East]->checkNeighbors(checked);
        if(m_neighbors[South])
        m_neighbors[South]->checkNeighbors(checked);
        if(m_neighbors[West])
        m_neighbors[West]->checkNeighbors(checked);
}

void paintpuz::findneighbor(Direction d)
{
        {
            if (m_neighbors[d]) return;
            if (connector_position[d] == None) return;
            QTransform tr;
            QPoint n;
            QPoint c;
            QPointF centre = mapToScene (0,0);
            paintpuz *nei = 0;
            int addSize = 1;

            switch (d) {
            case North:
                c = QPoint(centre.x(), centre.y() - PIECE_SIZE - addSize);
                n = QPoint(m_coordinates.x(), m_coordinates.y() -1 );
                nei = dynamic_cast<paintpuz*>(scene()->itemAt(c, tr));
                break;
            case South:
                c = QPoint(centre.x(), centre.y() + PIECE_SIZE + addSize);
                n = QPoint(m_coordinates.x(), m_coordinates.y() + 1 );
                nei = dynamic_cast<paintpuz*>(scene()->itemAt(c, tr));
                break;
            case East:
                c = QPoint(centre.x() + PIECE_SIZE + addSize, centre.y());
                n = QPoint(m_coordinates.x() + 1, m_coordinates.y());
                nei = dynamic_cast<paintpuz*>(scene()->itemAt(c, tr));
                break;
            case West:
                c = QPoint(centre.x() - PIECE_SIZE - addSize, centre.y());
                n = QPoint(m_coordinates.x() - 1, m_coordinates.y());
                nei = dynamic_cast<paintpuz*>(scene()->itemAt(c, tr));
                break;
            }
            if (nei)
                if (nei->coord() == n) link(nei, d);

        }

}
