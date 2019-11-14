#include "ratedit.h"

RatEdit::RatEdit(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setAutoFillBackground(true);
}

void RatEdit::setRating(int rate)
{
    mm_rating = rate;
}

int RatEdit::rating()
{
    return mm_rating;
}

void RatEdit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::yellow);
    int x=0;
    for (int i=1; i<=5; i++)
    {
        if(i>mm_rating)
            painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(x+2+i*16+i*2,0,16,16);
    }
}

void RatEdit::mouseMoveEvent(QMouseEvent *event)
{
    int c=position( event->x());
    if (c!=-1&&c!=mm_rating)
    {
        mm_rating=c;
        update();
    }
}

void RatEdit::mouseReleaseEvent(QMouseEvent *event)
{
    emit editingFinished();
}

int RatEdit::position(int p)
{
    int c=(p / 18);
    if (c<0||c>5)
        return -1;
    return c;
}

QSize RatEdit::sizeHint() const
{
    return QSize(108, 20);
}
