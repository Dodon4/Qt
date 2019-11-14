#include "ratingdelegate.h"
#include<QPainter>
#include"item.h"
#include"ratedit.h"
RatingDelegate::RatingDelegate()
{

}

RatingDelegate::RatingDelegate(int maxRange, QObject *parent):QStyledItemDelegate(parent), m_rat(maxRange)
{

}


void RatingDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int r;
    if(index.isValid()&&index.parent().isValid())
    {
        r = index.data().toInt();
        int x,y;
        x=option.rect.left();
        y=option.rect.top();
        painter->setPen(Qt::black);
        painter->setBrush(Qt::yellow);
        Item *item=static_cast<Item*>(index.internalPointer());
        if(item->toSong())
        {
            for(int i=1;i<=5;i++)
            {
                if(i>r)
                {
                  painter->setBrush(Qt::NoBrush);
                }
                painter->drawEllipse(x+2+i*16+i*2,y,16,16);
            }
        }
    }
}

QWidget *RatingDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid() && index.parent().isValid())
        {
            Item *item = static_cast<Item*>(index.internalPointer());
            if(item->toSong() && item->parent()->toAlbum())
            {
                RatEdit *editor = new RatEdit(parent);
                connect(editor, &RatEdit::editingFinished,this, &RatingDelegate::commitAndCloseEditor);
                return editor;
            }
            else
              return QStyledItemDelegate::createEditor(parent, option, index);
        }
        else
          return QStyledItemDelegate::createEditor(parent, option, index);
}

void RatingDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid()&&index.parent().isValid())
    {
        Item *item = static_cast<Item *>(index.internalPointer());
        if(item->toSong()&&item->parent()->toAlbum())
        {
            if(index.column() == 2)
            {
                int r= index.data().toInt();
                RatEdit *EditR = qobject_cast<RatEdit*>(editor);
                EditR->setRating(r);
            }
        else
          return QStyledItemDelegate::setEditorData(editor, index);
    }
    else
      return QStyledItemDelegate::setEditorData(editor, index);

    }
}

void RatingDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.isValid()&&index.parent().isValid())
    {
        Item *item = static_cast<Item *>(index.internalPointer());
        if(item->toSong() && item->parent()->toAlbum())
        {
            if(index.column() == 2)
            {
                RatEdit *ratingEditor = qobject_cast<RatEdit*>(editor);
                model->setData(index, QVariant::fromValue(ratingEditor->rating()));
            }
        else
         return QStyledItemDelegate::setEditorData(editor, index);
    }
    else
     return QStyledItemDelegate::setEditorData(editor, index);
    }
}

void RatingDelegate::commitAndCloseEditor()
{
    RatEdit *editor = qobject_cast<RatEdit*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
QSize RatingDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(108,20);

}
