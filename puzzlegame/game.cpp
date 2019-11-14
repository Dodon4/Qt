#include "game.h"
#include "paintpuz.h"
#include <QTime>
#include "puzzle.h"
#include "mainwindow.h"
#include <QRandomGenerator>
ConnectorPosition game:: reverse(ConnectorPosition pos) {
switch(pos){
    case None: return None;
    case In: return Out;
    case Out: return In;
    }
        return None;
}
void game::setup(QSize size, QPixmap pixmap)
{
    const int cellsize=PIECE_SIZE;
    clear();
    qsrand(QTime::currentTime().msec());
    ConnectorPosition storedWest;
    QVector<ConnectorPosition> prev(size.width(),None);
    for(int row=0; row<size.height();++row)
    {
        storedWest=None;
        for(int col=0;col<size.width();++col)
        {
        ConnectorPosition curr[4];
        curr[0]=reverse(prev[col]);
        curr[1]=qrand()%2 ? In : Out;
        curr[2]=qrand()%2 ? In : Out;
        curr[3]=reverse(storedWest);
        if(col==size.width()-1)
        curr[1]=None;
        if(row==size.height()-1)
        curr[2]=None;
        storedWest=curr[1];
        prev[col]=curr[2];

        paintpuz *piece = new paintpuz(curr[0],curr[1],curr[2],curr[3]);
        addItem(piece);
        piece->setFlag(QGraphicsItem::ItemIsMovable);
        piece->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
        piece->setPos(QRandomGenerator::global()->bounded(500-piece->size),QRandomGenerator::global()->bounded(500-piece->size));
        QRect rect=piece->boundingRect().toRect();
        rect.translate(0.5*cellsize+col*cellsize,0.5*cellsize+row*cellsize);
        QPixmap qim=pixmap.copy(rect);
        piece->setPixmap(qim);
        piece->setCoord(QPoint(col,row));
        piece->puzzle_item_count=size.width()*size.height();
        }

    }

}
