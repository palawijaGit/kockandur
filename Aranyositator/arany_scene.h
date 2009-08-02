#ifndef ARANY_SCENE_H
#define ARANY_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <iostream>

class AranyScene : public QGraphicsScene {

public:
    AranyScene();
    ~AranyScene(); 
    virtual void valami();
protected:

    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent ) ;

private:

    qreal down_x, down_y;

};

#endif // ARANY_SCENE_H
