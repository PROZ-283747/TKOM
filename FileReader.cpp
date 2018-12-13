// author: Adela Jaworowska / index: 283747

#include <iostream>
#include "FileReader.h"

FileReader::FileReader(const std::string &fileName) : handler("../" +fileName, std::ifstream::in){
    if(this->handler.fail()){
        std::cout<<"Failed to open the file."<<std::endl;
    }
}

const char FileReader::getNextChar()
{
    char sign;

    while (true)
    {
        sign = this->handler.get();
        if (sign == '\n' || sign == '\r')
        {
            this->lineNumber++;
            this->currentSignPos = 0;
        }

        this->prevChar = sign;
        this->currentSignPos++;

        return sign;
    }
}

void FileReader::rewind() {

    this->handler.unget().unget();
    this->prevChar = this->handler.get();
    auto peek = this->handler.peek();

    if (peek == '\n' || peek == '\r')
    {
        this->prevChar = this->handler.get();
        return;
    }
    this->currentSignPos--;
}

//  Returns the next character in the input sequence, without extracting it.
int FileReader::getPeek() {
    return handler.peek();
}


const bool FileReader::isEndOfFile()
{
    return this->handler.eof();
}
