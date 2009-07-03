#include <iostream>
#include <QApplication>
#include "sgf_parser/parser_main.h"
#include "mainwindow.h"

int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
    Parser parser;
    GobanWindow * gw = new GobanWindow;
    gw->show();
    if (argc > 1) {
        QString infile(argv[1]);
        parser.parseFile(infile);
    }
    return app.exec();

}
