#include "aranyositator_widget.h"

AranyositatorWidget::AranyositatorWidget(QWidget * parent) : QWidget(parent), scaleFactor(1.0)
{
    pictureLabel = new QLabel();
    pictureLabel->setBackgroundRole(QPalette::Base);
    pictureLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // pictureLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pictureLabel->setScaledContents(true);

    scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(pictureLabel);

    QWidget * editBox = new QWidget();
    QRect ebw;
    ebw.setWidth(100);
    editBox->setGeometry(ebw);
    editBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);



    editLayout = new QGridLayout();
    // editLayout->setAlignment(Qt::AlignTop);
    editLayout->addWidget( new QLineEdit(this),0, 1);
    editLayout->addWidget( new QLabel("A"),0, 0);
    editBox->setLayout(editLayout);
    // editBox->setAligment(Qt::AlignTop);

    QVBoxLayout * vLayout = new QVBoxLayout();
    vLayout->addWidget(editBox);
    vLayout->addStretch();

    QHBoxLayout * mainLayout = new QHBoxLayout();
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(vLayout);
    mainLayout->setAlignment(Qt::AlignTop);
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
    pictureLabel->resize(pictureLabel->pixmap()->size());
}

 AranyositatorWidget::~AranyositatorWidget() {

 }
