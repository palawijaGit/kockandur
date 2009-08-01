#include "arany_scene.h"

AranyScene::AranyScene() : QGraphicsScene() {
}

AranyScene::~AranyScene() {}

void AranyScene::valami() {
}

void AranyScene::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent ) {
    qreal x, y;
    std::cout << (x = mouseEvent->buttonDownScenePos(Qt::LeftButton).x()) << std::endl;
    std::cout << (y = mouseEvent->buttonDownScenePos(Qt::LeftButton).y()) << std::endl;

    this->addEllipse(x-5, y-5, 10.0, 10.0);
}
