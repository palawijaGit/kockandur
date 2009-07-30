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
#include <QGraphicsScene>
#include <iostream>

class AranyositatorWidget : public QWidget
{

     Q_OBJECT

    public:

        AranyositatorWidget(QWidget * parent);        
        virtual ~AranyositatorWidget();

    private:

        QGraphicsView * grafView;
        QGraphicsScene * scene;
        QScrollArea * scrollArea;
        QGridLayout * editLayout;

        float scaleFactor;

    public slots:

        void zoomin();
        void zoomout();        
        void zoomnormal();
        void loadFile(QString & fileName);
};

#endif // ARANYOSITATOR_WIDGET_H
