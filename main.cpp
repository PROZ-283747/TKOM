// author: Adela Jaworowska / index: 283747

#include <iostream>
#include "Lexer.h"


int main() {

    std::string fileName;
    std::cout << "Enter file name: ";
    std::cin >> fileName;

    //FileReader fileReader = FileReader(fileName);
    Lexer lekser(fileName);

    do{
        lekser.nextToken();
        if((*lekser.tokenPtr).type == ERROR)
            exit(0);
    }while((*lekser.tokenPtr).type != END_OF_FILE);

    std::cout <<std::endl<< "THIS IS THE END." <<std::endl;

    return 0;
}