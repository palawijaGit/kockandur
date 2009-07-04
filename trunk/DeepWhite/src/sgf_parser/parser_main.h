#ifndef PARSER_MAIN_H
#define PARSER_MAIN_H

#include <QRegExp>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QChar>
#include "sgf_collection.h"
#include "sgf_tree.h"

class Parser {
    public:
        SgfCollection * parseFile(const QString&);
        bool isUCLetter(QChar) const;
        bool isDigit(QChar) const;
        bool isSign(QChar) const;
        bool isNumber(const QString&) const;
        bool isDouble(const QChar) const;
        bool isColor(const QChar) const;
        bool isRealStrict(const QString&) const;
        QString parseTokken(QTextStream &);
        void parseCollection(QTextStream &);
        void parseGameTree(QTextStream &, SgfTree & );
        void parseSequence(QTextStream &);
    private:

};

#endif // PARSER_MAIN_H
