// author: Adela Jaworowska / index: 283747

#ifndef TKOM_ERRORHANDLER_H
#define TKOM_ERRORHANDLER_H

#include <string>
#include <iostream>
#include "Token.h"

class ErrorHandler{
public:
    ErrorHandler(){}
    ~ErrorHandler(){}
    void printError(std::string module, const Token &token, std::string errorMsg){
        std::cout<< "*************************"<<std::endl;
        std::cout<< "Error in: "<< module << " : " << errorMsg << " line: "<< token.line << " pos: "<< token.positionInLine <<std::endl;
        std::cout<< "*************************"<<std::endl;
    }
private:


};
#endif //TKOM_ERRORHANDLER_H
