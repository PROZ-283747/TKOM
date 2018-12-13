// author: Adela Jaworowska / index: 283747

#ifndef TKOM_FILEREADER_H
#define TKOM_FILEREADER_H

#include <string>
#include <fstream>
#include <iostream>

class FileReader {
public:
    unsigned int lineNumber = 1;
    unsigned int currentSignPos = 0;

    FileReader(const std::string &fileName);
    const char getNextChar();
    void rewind();
    const bool isEndOfFile();
    int getPeek();

private:
    char prevChar; // holds sign that was returned after returning it
    std::ifstream handler;

};


#endif //TKOM_FILEREADER_H