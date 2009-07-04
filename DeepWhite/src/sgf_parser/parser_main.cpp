#include "parser_main.h"
#include <iostream>
#include <exception>

QString ParseTokken(QTextStream &in) {
    static QChar last;
    QChar c;
    QString sum;
    in >> c;
    switch (c.toAscii()) {
        case '(':
        case ';':
        case ')':
        case '[':
        case ']':
        case '\\': return c;
    }    
    return "";
}

bool Parser::isUCLetter(QChar c) const {
        if ('A' <= c && c <= 'Z') return true;
        return false;
}

bool Parser::isDigit(QChar c) const {
        return c.isDigit();
}

bool Parser::isSign(QChar c) const {
        return (c == '+' || c == '-');
}

bool Parser::isNumber(const QString & value) const {
    bool was_sign = false;
    if (value.isEmpty()) return false;
    if (isSign(value.data()[0])) was_sign = true;
    if (!was_sign && !isDigit(value.data()[0])) return false;
    if (was_sign && value.length() == 1) return false;
    for (int i = 1; i < value.length(); i++)
        if (!isDigit(value.data()[i])) return false;
    return true;
}

bool Parser::isRealStrict(const QString &value) const {
    if (isNumber(value)) return true;               // We accept integers as floats
    int dot_pos = value.indexOf('.');
    if (dot_pos <= 0) return false;                 // Its not a number and the problem was not the dot, or only starts with a dot
                                                    // A number required before the dot
    if ((dot_pos + 1) == value.length()) return false; // Dot is the last char (A digit required if there was a dot)
    for (int i = dot_pos+1; i < value.length(); i++)
        if (!isDigit(value.data()[i])) return false; // The end is not
    return true;
}

bool Parser::isColor(QChar c) const {
     return (c == 'B' || c == 'W');
}

bool Parser::isDouble(QChar c) const {
     return (c == '1' || c == '2');
}

void Parser::parseCollection(QTextStream & in) {
    // while(!in.atEnd())
    //     parseGameTree(in);
}

void Parser::parseGameTree(QTextStream & in, SgfTree & tree) {
    QChar c;
    in >> c;
    // if (c == '(') c = parseSequence(in, tree);

}

void Parser::parseSequence(QTextStream & in){
}

SgfCollection * Parser::parseFile(const QString & infile) {
    // QString some = ParseTokken(in);


    QFile game_file(infile);
    if (game_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        char c;
        while (!game_file.atEnd()) {
            game_file.getChar(&c);
            std::cout << c;
            game_file.ungetChar(c);
            game_file.getChar(&c);
            std::cout << c;
        }
        std::cout << std::endl;
    } else {
       //  throw exception("Unable to read file");
    }
    return new SgfCollection();
}

