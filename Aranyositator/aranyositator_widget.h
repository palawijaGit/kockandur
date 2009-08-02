#ifndef ARANYOSITATOR_WIDGET_H
#define ARANYOSITATOR_WIDGET_H

#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QScrollArea>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRect>
#include <QSizePolicy>
#include <QLineEdit>
#include <QGraphicsView>
#include <arany_scene.h>
#include <iostream>

class AranyositatorWidget : public QWidget
{

     Q_OBJECT

    public:

        AranyositatorWidget(QWidget * parent);        
        virtual ~AranyositatorWidget();

    private:

        QGraphicsView * grafView;
        AranyScene * scene;
        QScrollArea * scrollArea;
        QGridLayout * editLayout;

        float scaleFactor;

    public slots:

        void zoomin();
        void zoomout();        
        void zoomnormal();
        void loadFile(QString & fileName);
        void addNewItem(qreal x1, qreal y1, qreal x2, qreal y2);

};

class AranyItem {
    private:
        qreal x1, y1, x2, y2;
        QLineEdit * editbox;
    signals:
        void valueChanged(qreal factor);
};

#endif // ARANYOSITATOR_WIDGET_H
