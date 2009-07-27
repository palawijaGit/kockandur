#include "aranyositator.h"

aranyositator::aranyositator(QWidget *parent) : QMainWindow(parent)
{
    arany = new AranyositatorWidget(this);

    createActions();
    createMenus();
    setCentralWidget(arany);

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
    connect(zoominAction, SIGNAL(triggered()), arany, SLOT(zoomin()));

    zoomoutAction = new QAction(tr("Zoom o&ut"), this);
    connect(zoomoutAction, SIGNAL(triggered()), arany, SLOT(zoomout()));

    closeAction = new QAction(tr("&Quit"), this);
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
}

void aranyositator::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Picture"), ".",
                                                    tr("Image files (*.jpg *.bmp *.png *.gif)"));
    if (!fileName.isEmpty())
        arany->loadFile(fileName);
}

void aranyositator::about() {

}
