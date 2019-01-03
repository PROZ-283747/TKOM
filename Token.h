// author: Adela Jaworowska / index: 283747

#ifndef TKOM_TOKEN_H
#define TKOM_TOKEN_H

#include <string>
#include <iostream>
#include "TokenType.h"
#include "Fraction.h"

using namespace token;

struct Token {
    Type type;
    union{
        std::string stringValue = "";
        Fraction fraction;
    };
    unsigned int line = 0;
    unsigned int positionInLine = 0;

    ~Token() {}
    //Token(const Type& type,  std::string &val, unsigned int line, unsigned int pos) : type(type), stringValue(val), line(line), positionInLine(pos)  {}
    Token(Type type, std::string value, unsigned int line, unsigned int posLine) {
        this->type = type;
        stringValue = value;
        this->line = line;
        this->positionInLine = posLine;
        if(type == NUMBER){
            fraction = Fraction(value);
            std::cout<<"Nominator: "<<fraction.getNominator()<<std::endl;
            std::cout<<"Denominator: "<<fraction.getDenominator()<<std::endl;
        }
    }

};
// Token jako struktura, albo classe i ustawić settery i gettery; prontToken to gdzieś indziej, zeby nie narzucac sposobu drukowania tokenu.
#endif //TKOM_TOKEN_H
