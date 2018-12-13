// author: Adela Jaworowska / index: 283747

#ifndef TKOM_TOKEN_H
#define TKOM_TOKEN_H

#include <string>
#include <iostream>
#include "TokenType.h"

using namespace token;

class Token {
public:
    Token(const Type& t) : type(t){}
    Token(){}

    Type type;
    std::string value ="";
    unsigned int line = 0;
    unsigned int positionInLine = 0;

    void printToken(){
        std::cout<< "TOKEN: "<< " type: " << type << " value: \""<< value << "\" line:  " << line << " poss: " << positionInLine << std::endl;
    }
};

#endif //TKOM_TOKEN_H
