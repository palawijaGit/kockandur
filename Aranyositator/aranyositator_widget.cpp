#include "aranyositator_widget.h"

AranyositatorWidget::AranyositatorWidget(QWidget * parent) : QWidget(parent), scaleFactor(1.0)
{
    scene = new AranyScene();
    grafView = new QGraphicsView(scene);

    // pictureLabel = new QLabel();
    // pictureLabel->setBackgroundRole(QPalette::Base);
    grafView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // pictureLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // pictureLabel->setScaledContents(true);

    // scrollArea = new QScrollArea();
    // scrollArea->setBackgroundRole(QPalette::Dark);
    // scrollArea->setWidget(grafView);

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
    mainLayout->addWidget(grafView);
    mainLayout->addLayout(vLayout);
    mainLayout->setAlignment(Qt::AlignTop);
    this->setLayout(mainLayout);
}

void AranyositatorWidget::zoomin() {

    scaleFactor *= 1.25;
    grafView->scale(1.25, 1.25);
}

void AranyositatorWidget::zoomout() {
    scaleFactor *= 0.8;
    grafView->scale(0.8, 0.8);
}

void AranyositatorWidget::zoomnormal() {
    grafView->scale( 1.0 / scaleFactor, 1.0 / scaleFactor);
    scaleFactor = 1.0;
}

 void AranyositatorWidget::loadFile(QString & fileName) {
    std::cout << fileName.toStdString();

    QPixmap pic2(fileName);

    grafView->scene()->clear();
    
    grafView->scene()->addPixmap(pic2);
}

 AranyositatorWidget::~AranyositatorWidget() {

 }
