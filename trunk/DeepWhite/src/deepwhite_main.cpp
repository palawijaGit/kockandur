#include <iostream>
#include <QApplication>
#include "sgf_parser/parser_main.h"
#include "mainwindow.h"

int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
    Parser parser;
    GobanWindow * gw = new GobanWindow;
    gw->show();
    QString infile(argv[1]);
    parser.parseFile(infile);
    std::cout << "Próba \n";
    return app.exec();

}
