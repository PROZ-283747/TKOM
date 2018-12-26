// author: Adela Jaworowska / index: 283747

#include <iostream>
#include "Lexer.h"


int main() {

    std::string string = "monstera";
    int pos = string.find("r");
    std::cout<<"pos: " <<pos<<std::endl;
    int pos2 = string.find("x");
    std::cout<<"pos2: " <<pos2<<std::endl;

    std::string str = "456";
    std::cout<<"int: " <<stoi(str)<<std::endl;
//    std::string fileName;
//    std::cout << "Enter file name: ";
//    std::cin >> fileName;
//
//    Lexer lekser(fileName);
//    Token token;
//
//    do{
//        token = lekser.nextToken();
//    }while(token.type != END_OF_FILE);
//
//    std::cout<<std::endl;
//    std::cout << "THIS IS THE END." <<std::endl;

    return 0;
}