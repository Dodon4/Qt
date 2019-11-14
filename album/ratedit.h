#ifndef RATEDIT_H
#define RATEDIT_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
class RatEdit : public QWidget
{
    Q_OBJECT
public:
    explicit RatEdit(QWidget *parent = nullptr);
    void setRating(int rate);
    int rating(void);
    QSize sizeHint() const;
    int position(int p);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int mm_rating;

signals:
    void editingFinished();
};

#endif // RATEDIT_H
