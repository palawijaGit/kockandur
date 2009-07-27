#ifndef ARANYOSITATOR_H
#define ARANYOSITATOR_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QString>
#include "aranyositator_widget.h"

class aranyositator : public QMainWindow
{
    Q_OBJECT

private:

    QMenu * fileMenu;
    QMenu * viewMenu;
    QMenu * aboutMenu;
    QAction * openAction;
    QAction * closeAction;
    QAction * aboutAction;
    QAction * zoominAction;
    QAction * zoomoutAction;

    AranyositatorWidget * arany;

public:
    aranyositator(QWidget *parent = 0);
    ~aranyositator();

private slots:
    void open();
    void about();

private:
    void createMenus();
    void createActions();

};

#endif // ARANYOSITATOR_H
