#ifndef GAME_H
#define GAME_H
#include "paintpuz.h"
#include <QGraphicsScene>
class game : public QGraphicsScene
{
public:
     ConnectorPosition reverse(ConnectorPosition pos);
    game(){}
    ~game(){}
    void setup(QSize size,QPixmap pixmap);
};

#endif
