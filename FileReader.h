// author: Adela Jaworowska / index: 283747

#ifndef TKOM_FILEREADER_H
#define TKOM_FILEREADER_H

#include <string>
#include <fstream>
#include <iostream>

class FileReader {
public:

    FileReader(const std::string &fileName);
    const void getNextChar();
    void rewind();
    const bool isEndOfFile();
    int peek();
    char getSign() const;
    void setSign(char sign);
    void setPrevSign(char prevSign);
    void setLineNumber(unsigned int lineNumber);
    void setCurrentSignPos(unsigned int currentSignPos);
    char getPrevSign() const;
    unsigned int getLineNumber() const;
    unsigned int getCurrentSignPos() const;


private:
    char sign; // last sign read by FileReader
    char prevSign;
    unsigned int lineNumber = 1;
    unsigned int currentSignPos = 0;

    std::ifstream handler;

};


#endif //TKOM_FILEREADER_H