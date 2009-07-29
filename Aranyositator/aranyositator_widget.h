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
#include <iostream>

class AranyositatorWidget : public QWidget
{

     Q_OBJECT

    public:

        AranyositatorWidget(QWidget * parent);        
        virtual ~AranyositatorWidget();

    private:

        QLabel * pictureLabel;
        QScrollArea * scrollArea;
        QGridLayout * editLayout;

        float scaleFactor;

    public slots:

        void zoomin();
        void zoomout();        
        void loadFile(QString & fileName);
        void adjustScrollBar(QScrollBar *scrollBar, double factor);
};

#endif // ARANYOSITATOR_WIDGET_H
