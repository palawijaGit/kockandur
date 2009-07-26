#include "aranyositator.h"

aranyositator::aranyositator(QWidget *parent)
    : QMainWindow(parent), scaleFactor(1.0)
{
    createActions();
    createMenus();
    pictureLabel = new QLabel();
    pictureLabel->setBackgroundRole(QPalette::Base);
    pictureLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    pictureLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(pictureLabel);

    QHBoxLayout * mainLayout = new QHBoxLayout();
    mainLayout->addWidget(scrollArea);
    // setCentralWidget(mainLayout);
    // setLayout(mainLayout);    
    this->layout()->addItem(mainLayout);
    //this->layout()->addChildLayout(mainLayout);

    setWindowTitle(tr("Aranyositator"));
    resize(500, 400);
}

aranyositator::~aranyositator()
{

}

void aranyositator::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);

    viewMenu = menuBar()->addMenu(tr("&Edit"));
    viewMenu->addAction(zoominAction);
    viewMenu->addAction(zoomoutAction);

    aboutMenu = menuBar()->addMenu(tr("&About"));
    aboutMenu->addAction(aboutAction);
}

void aranyositator::createActions() {
    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    zoominAction = new QAction(tr("Zoom &in"), this);
    connect(zoominAction, SIGNAL(triggered()), this, SLOT(zoomin()));

    zoomoutAction = new QAction(tr("Zoom o&ut"), this);
    connect(zoomoutAction, SIGNAL(triggered()), this, SLOT(zoomout()));

    closeAction = new QAction(tr("&Quit"), this);
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
}

void aranyositator::loadFile(QString & fileName) {
    std::cout << fileName.toStdString();
    QImage image(fileName);
    pictureLabel->setPixmap(QPixmap::fromImage(image));
}

void aranyositator::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Picture"), ".",
                                                    tr("Image files (*.jpg *.bmp *.png *.gif)"));
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void aranyositator::about() {

}

void aranyositator::zoomin() {

    scaleFactor *= 1.25;
    pictureLabel->resize(scaleFactor * pictureLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), 1.25);
    adjustScrollBar(scrollArea->verticalScrollBar(), 1.25);
}

void aranyositator::zoomout() {
    scaleFactor *= 0.8;
    pictureLabel->resize(scaleFactor * pictureLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), 0.8);
    adjustScrollBar(scrollArea->verticalScrollBar(), 0.8);
}

 void aranyositator::adjustScrollBar(QScrollBar *scrollBar, double factor)
 {
     scrollBar->setValue(int(factor * scrollBar->value()
                             + ((factor - 1) * scrollBar->pageStep()/2)));
 }
