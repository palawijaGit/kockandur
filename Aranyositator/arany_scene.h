#ifndef ARANY_SCENE_H
#define ARANY_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

class AranyScene : public QGraphicsScene {

public:
    AranyScene();
    ~AranyScene(); 
    virtual void valami();
protected:
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
};

#endif // ARANY_SCENE_H
