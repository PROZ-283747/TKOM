// author: Adela Jaworowska / index: 283747

#include <iostream>
#include "Lexer.h"


int main() {

    std::string fileName;
    std::cout << "Enter file name: ";
    std::cin >> fileName;

    Lexer lekser(fileName);
    Token token;

    do{
        token = lekser.nextToken();
    }while(token.type != END_OF_FILE);

    std::cout<<std::endl;
    std::cout << "THIS IS THE END." <<std::endl;

    return 0;
}