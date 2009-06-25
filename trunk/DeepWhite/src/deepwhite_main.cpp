#include <iostream>
#include "sgf_parser/parser_main.h"

int main(int argc, char * argv[]) {
    Parser parser;
    QString infile(argv[1]);
    parser.parseFile(infile);
    std::cout << "Próba \n";
    return 0;    
}
