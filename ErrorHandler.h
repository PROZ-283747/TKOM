// author: Adela Jaworowska / index: 283747

#ifndef TKOM_ERRORHANDLER_H
#define TKOM_ERRORHANDLER_H

#include <string>
#include <iostream>
#include <memory>
#include "Token.h"

class ErrorHandler{
public:
    ErrorHandler(){}
    ~ErrorHandler(){}
    void printError(std::string module, unsigned int line, unsigned int pos, std::string errorMsg){
        std::cout<< "*************************"<<std::endl;
        std::cout<< "Error in: "<< module << " : " << errorMsg << " line: "<< line << " pos: "<< pos <<std::endl;
        std::cout<< "*************************"<<std::endl;
    }

};
#endif //TKOM_ERRORHANDLER_H
