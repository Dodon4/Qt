#ifndef RATINGDELEGATE_H
#define RATINGDELEGATE_H
#include<QStyledItemDelegate>

class RatingDelegate : public QStyledItemDelegate
{
public:
    RatingDelegate();
    explicit RatingDelegate(int maxRange, QObject *parent = nullptr);
    int m_rat;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;

private slots:
    void commitAndCloseEditor();
};

#endif // RATINGDELEGATE_H
