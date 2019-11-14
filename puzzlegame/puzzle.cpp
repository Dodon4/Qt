#include "puzzle.h"
#include "mainwindow.cpp"

QSize puzzle::min() const
{
    return m_min;
}

QSize puzzle::max() const
{
    return m_max;
}

QPixmap puzzle::prev() const
{
    return m_prev;
}


void puzzle::setPrev(QPixmap prev)
{
    m_prev = prev;
}

puzzle::puzzle(QWidget *parent): QFrame(parent)
{
    m_size=QSize(6,5);
    m_min=QSize(2,2);
    m_max=QSize(8,8);
}

QSize puzzle::cellSize() const
{
    int w =width();
    int h = height();
    int mw = max().width();
    int mh = max().height();
    int extent =qMin(w/mw,h/mh);
    return QSize(extent,extent).expandedTo(QApplication::globalStrut()).expandedTo(QSize(4,4));
}

QPoint puzzle::cellAt(const QPoint &mouse_point) const
{
    QSize cs=cellSize();
    int x = mouse_point.x()/cs.width()+1;
    int y = mouse_point.y()/cs.height()+1;
    return QPoint(x,y);
}

void puzzle::renderPreview(QPainter *painter)
{
 QSize cell_size = cellSize();
 if(!m_prev.isNull()){
     QSize sz(cell_size.width()*Value().width(),cell_size.height()*Value().height());
     painter->drawPixmap(0,0,m_prev.scaled(sz));
 }else{
     painter->setBrush(QBrush(Qt::gray));
     painter->drawRect(0,0,cell_size.width()*Value().width(),cell_size.height()*Value().height());
 }

}
void puzzle::renderGrid(QPainter *painter)
{
   QSize cell_size = cellSize();
   painter->setBrush(Qt::NoBrush);
   for(int x=0;x<m_max.width();x++)
       for(int y=0;y<m_max.height();y++){
           painter->drawRect(x*cell_size.width(),y*cell_size.height(),cell_size.width(),cell_size.height());
       }
}

void puzzle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    renderPreview(&painter);
    renderGrid(&painter);
}

QSize puzzle::SizeHint() const
{
    return QSize(300,300);
}

void puzzle::mousePressEvent(QMouseEvent *event)
{
    QPoint mp = event->pos();
    QPoint cell = cellAt(mp);
    if(cell.x()>=min().width() && cell.x()<=max().width() &&
        cell.y()>=min().height() && cell.y()<=max().height())
        setValue(QSize(cell.x(),cell.y()));
}

void puzzle::mouseMoveEvent(QMouseEvent *event)
{
    QPoint mp = event->pos();
    QPoint cell = cellAt(mp);
    if(cell.x()>=min().width() && cell.x()<=max().width() &&
        cell.y()>=min().height() && cell.y()<=max().height())
        setValue(QSize(cell.x(),cell.y()));
}

QSize puzzle::Value() const
{
    return m_size;
}

void puzzle::setValue(QSize value)
{
    if(value == m_size)
        return;
    m_size=value;
    if (value.height()>m_max.height() ||
        value.width()>m_max.width() ||
        value.height()<m_min.height() ||
        value.width()<m_min.width())
        return;
    update();
}

void puzzle::setMin(QSize min)
{
    m_min=min;
}

void puzzle::setMax(QSize max)
{
   m_max=max;
}
