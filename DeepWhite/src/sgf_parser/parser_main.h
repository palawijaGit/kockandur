#ifndef PARSER_MAIN_H
#define PARSER_MAIN_H

#include <QRegExp>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "sgf_tree.h"

class Parser {
    public:
        SgfTree parseFile(QString & filename);
    private:
};

#endif // PARSER_MAIN_H
