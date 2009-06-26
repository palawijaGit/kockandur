#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>

class GobanWindow : public QMainWindow {


    private:

         QMenu      * fileMenu;
         QMenu      * aboutMenu;
         QAction    * newAction;
         QAction    * openAction;

    public:

        GobanWindow();
        ~GobanWindow();
        void createMenus();
        void createActions();

};

#endif // MAINWINDOW_H
