#include "arany_scene.h"

AranyScene::AranyScene() : QGraphicsScene() {
}

AranyScene::~AranyScene() {}

void AranyScene::valami() {
}

void AranyScene::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent ) {
    down_x = mouseEvent->buttonDownScenePos(Qt::LeftButton).x();
    down_y = mouseEvent->buttonDownScenePos(Qt::LeftButton).y();
}

void AranyScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent ) {
    qreal x, y;
    x = mouseEvent->scenePos().x();
    y = mouseEvent->scenePos().y();

    QPen pen(Qt::red);
    QBrush fill(Qt::green);
    this->addEllipse(down_x-5, down_y-5, 10.0, 10.0, pen, fill);
    this->addEllipse(x-5, y-5, 10.0, 10.0, pen, fill);
    this->addLine(down_x, down_y, x, y, pen);
#ifdef DEBUG
    std::clog << "Line from x: " << down_x << "-" << x << " diff :" << down_x - x  std::endl;
    std::clog << "Line from y: " << down_y << "-" << y << " diff :" std::endl;
#endif
}
