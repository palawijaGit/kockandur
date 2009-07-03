#include "parser_main.h"
#include <iostream>
#include <exception>

QString ParseTokken(QTextStream &in) {
    QChar c;
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

bool Parser::isReal(const QString &value) const {
    if (isNumber(value)) return true;               // We accept integers as floats
    int dot_pos = value.indexOf('.');
    if (dot_pos <= 0) return false;                 // Its not a number and the problem was not the dot, or only starts with a dot
                                                    // A number required before the dot
    if ((dot_pos + 1) == value.length) return false; // Dot is the last char (A digit required if there was a dot)
    for (int i = dot_pos; i < value.length(); i++)
        if (!isDigit(value.data()[i])) return false; // The end is not
}


SgfTree Parser::parseFile(QString & infile) {
    // QString some = ParseTokken(in);
    std::cout << "C isUCLetter: " << isUCLetter('C') << std::endl;
    std::cout << "c isUCLetter: " << isUCLetter('c') << std::endl;
    std::cout << "1 isUCLetter: " << isUCLetter('1') << std::endl;
    std::cout << "C isDigit: " << isDigit('C') << std::endl;
    std::cout << "c isDigit: " << isDigit('c') << std::endl;
    std::cout << "1 isDigit: " << isDigit('1') << std::endl;
    std::cout << "1 isNumber: " << isNumber("1") << std::endl;
    std::cout << "1121 isNumber: " << isNumber("1121") << std::endl;
    std::cout << "+1 isNumber: " << isNumber("+1") << std::endl;
    std::cout << "-1 isNumber: " << isNumber("-1") << std::endl;
    std::cout << "SD isNumber: " << isNumber("SD") << std::endl;
    std::cout << "123D isNumber: " << isNumber("123D") << std::endl;
    std::cout << "+ isNumber: " << isNumber("+") << std::endl;


    /* QFile game_file(infile);
    if (game_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&game_file);
        while (!in.atEnd()) {

        }
    } else {
        // throw exception("Unable to read file");
    }*/
}

