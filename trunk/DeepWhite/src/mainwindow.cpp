#include "mainwindow.h"

GobanWindow::GobanWindow() {
    createActions();
    createMenus();
}

GobanWindow::~GobanWindow() {
}

void GobanWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    aboutMenu = menuBar()->addMenu(tr("&About"));
}

void GobanWindow::createActions() {
    newAction = new QAction(tr("&New"), this);
    openAction = new QAction(tr("&Load"), this);
}
