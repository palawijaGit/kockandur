#ifndef PARSER_MAIN_H
#define PARSER_MAIN_H

#include <QRegExp>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QChar>
#include "sgf_tree.h"

class Parser {
    public:
        SgfTree parseFile(const QString&);
        bool isUCLetter(QChar) const;
        bool isDigit(QChar) const;
        bool isSign(QChar) const;
        bool isNumber(const QString&) const;
        bool isFloat(const QString&) const;
        QString parseTokken(QTextStream &);
    private:

};

#endif // PARSER_MAIN_H
