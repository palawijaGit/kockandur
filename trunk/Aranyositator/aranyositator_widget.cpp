#include "aranyositator_widget.h"

AranyositatorWidget::AranyositatorWidget(QWidget * parent) : QWidget(parent), scaleFactor(1.0)
{
    pictureLabel = new QLabel();
    pictureLabel->setBackgroundRole(QPalette::Base);
    pictureLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pictureLabel->setScaledContents(true);

    scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(pictureLabel);

    editGroup = new QGroupBox();

    QWidget * box = new QWidget();
    QRect q;
    q.setWidth(100);
    box->setGeometry(q);
    box->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QVBoxLayout * editLayout = new QVBoxLayout();
    editLayout->addWidget( new QLineEdit(this));
    editLayout->addWidget( new QLineEdit(this));
    editLayout->addWidget( new QLineEdit(this));
    editLayout->addWidget( new QLineEdit(this));
    pictureLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);    
    QHBoxLayout * mainLayout = new QHBoxLayout();
    box->setLayout(editLayout);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(box);
    this->setLayout(mainLayout);
}

void AranyositatorWidget::zoomin() {

    scaleFactor *= 1.25;
    pictureLabel->resize(scaleFactor * pictureLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), 1.25);
    adjustScrollBar(scrollArea->verticalScrollBar(), 1.25);
}

void AranyositatorWidget::zoomout() {
    scaleFactor *= 0.8;
    pictureLabel->resize(scaleFactor * pictureLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), 0.8);
    adjustScrollBar(scrollArea->verticalScrollBar(), 0.8);
}

 void AranyositatorWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
 {
     scrollBar->setValue(int(factor * scrollBar->value()
                             + ((factor - 1) * scrollBar->pageStep()/2)));
 }

 void AranyositatorWidget::loadFile(QString & fileName) {
    std::cout << fileName.toStdString();
    QImage image(fileName);
    pictureLabel->setPixmap(QPixmap::fromImage(image));
    pictureLabel->resize(
}

 AranyositatorWidget::~AranyositatorWidget() {

 }
