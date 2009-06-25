#include "parser_main.h"
#include <iostream>
#include <exception>

SgfTree Parser::parseFile(QString & infile) {
    QFile game_file(infile);
    if (game_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&game_file);
        while (!in.atEnd()) {
              QString line = in.readLine();
              std::cout << line.toStdString() << std::endl;
        }
    } else {
        // throw exception("Unable to read file");
    }
}


