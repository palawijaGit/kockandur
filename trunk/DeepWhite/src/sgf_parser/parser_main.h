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

        struct ParserException {
            const char * er;
            ParserException(const char * e) { er = e; }
            };
        SgfCollection * parseFile(const QString&);
        bool isUCLetter(QChar) const;
        bool isDigit(QChar) const;
        bool isSign(QChar) const;
        bool isNumber(const QString&) const;
        bool isDouble(const QChar) const;
        bool isColor(const QChar) const;
        bool isRealStrict(const QString&) const;
        QString parseTokken(QTextStream &);
        SgfCollection * parseCollection(QIODevice &);
        SgfTree       * parseGameTree(QIODevice &);
        SgfSequence   * parseSequence(QIODevice &);
        void parseSequence(QTextStream &);
    private:

};

#endif // PARSER_MAIN_H
