#ifndef ARANYOSITATOR_H
#define ARANYOSITATOR_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QScrollArea>
#include <QScrollBar>
#include <QHBoxLayout>
#include <iostream>

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
    QLabel * pictureLabel;
    QPixmap * picture;
    QScrollArea * scrollArea;

    float scaleFactor;

public:
    aranyositator(QWidget *parent = 0);
    ~aranyositator();

private slots:
    void open();
    void about();
    void zoomin();
    void zoomout();

private:
    void createMenus();
    void createActions();

    void loadFile(QString & fileName);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

};

#endif // ARANYOSITATOR_H
