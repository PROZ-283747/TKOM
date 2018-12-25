// author: Adela Jaworowska / index: 283747

#include <iostream>
#include "FileReader.h"

FileReader::FileReader(const std::string &fileName) : handler("../" +fileName, std::ifstream::in){
    if(this->handler.fail()){
        std::cout<<"Failed to open the file."<<std::endl;
    }
}

const void FileReader::getNextChar()
{
    // EOF zamienić na end of text ETX

        this->sign = this->handler.get();
        if (sign == '\n' || sign == '\r')
        {
            this->lineNumber++;
            this->currentSignPos = 0;
        }
        this->prevSign = sign;
        this->currentSignPos++;
}

void FileReader::rewind() {

    this->handler.unget().unget();
    this->prevSign = this->handler.get();
    auto peek = this->handler.peek();

    if (peek == '\n' || peek == '\r')
    {
        this->prevSign = this->handler.get();
        return;
    }
    this->currentSignPos--;
}

//  Returns the next character in the input sequence, without extracting it.
int FileReader::peek() {
    return handler.peek();
}


const bool FileReader::isEndOfFile() {
    return this->handler.eof();
}

void FileReader::setSign(char sign) {
    FileReader::sign = sign;
}

char FileReader::getSign() const {
    return sign;
}

char FileReader::getPrevSign() const {
    return prevSign;
}

unsigned int FileReader::getLineNumber() const {
    return lineNumber;
}

unsigned int FileReader::getCurrentSignPos() const {
    return currentSignPos;
}

void FileReader::setPrevSign(char prevSign) {
    FileReader::prevSign = prevSign;
}

void FileReader::setLineNumber(unsigned int lineNumber) {
    FileReader::lineNumber = lineNumber;
}

void FileReader::setCurrentSignPos(unsigned int currentSignPos) {
    FileReader::currentSignPos = currentSignPos;
}

