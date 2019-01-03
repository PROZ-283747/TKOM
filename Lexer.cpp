// author: Adela Jaworowska / index: 283747

#include <winnt.h>
#include "Lexer.h"
#include "ErrorHandler.h"


Lexer::Lexer(const std::string &fileName) : fileReader(fileName){}

const void Lexer::handleError(unsigned int line, unsigned int pos, std::string errorMsg) {
    ErrorHandler errorHandler = ErrorHandler();
    errorHandler.printError("LEXER", line, pos, errorMsg);
}

// for testing purposes -> to delete
void printToken(std::unique_ptr<Token> const &token){
    std::cout<< "TOKEN: "<< " type: " << token->type << " value: \""<< token->stringValue << "\" line:  " << token->line << " poss: " << token->positionInLine << std::endl;
}

bool Lexer::isEndOfFile(){
    return fileReader.getSign() == EOF;
}

std::unique_ptr<Token> Lexer::createEndOfFile(unsigned int line, unsigned int posInLine){
    std::cout<<"create end of file"<<std::endl;
    tokenPtr = std::make_unique<Token>(Type::END_OF_FILE, "End of file", line, posInLine);
    return std::make_unique<Token>(Type::END_OF_FILE, "End of file", line, posInLine);
}

void Lexer::skipUnrelevant(){
    std::cout<<"Skip unrelevant"<<std::endl;
    while(true) {
        auto c = this->fileReader.getNextChar();
        while(isspace(c)){
            c = this -> fileReader.getNextChar();
        }
        switch(c){
            case '\r':
            case '\t':
                break;
            case '#': // Skips comments.
                while(fileReader.peek() != '\n' && fileReader.peek() != EOF)
                    fileReader.getNextChar();
                break;
            default:
                return;
        }
    }
}

std::unique_ptr<Token> Lexer::createDigit(unsigned int line, unsigned int posInLine){
    std::cout<<"createDigit"<<std::endl;
    auto c = this->fileReader.getSign();
    std::string buffer;
    do {
        buffer.push_back(c);
        c = this->fileReader.getNextChar();
    } while (isdigit(c));
    if(fileReader.getSign() == '%' && isdigit(fileReader.peek())) {
        do{
            buffer.push_back(c);
            c = this->fileReader.getNextChar();
        }
        while(isdigit(c));
    }
    fileReader.rewind();

    tokenPtr = std::make_unique<Token>(Type::NUMBER, buffer.c_str(), line, posInLine);
    return std::make_unique<Token>(Type::NUMBER, buffer.c_str(), line, posInLine);
}

std::unique_ptr<Token> Lexer::createIdentifier(unsigned int line, unsigned int posInLine) {
    std::cout<<"createIdentifier"<<std::endl;
    auto c = this->fileReader.getSign();
    std::string buffer;
    do{
        buffer.push_back(c);
        c = this->fileReader.getNextChar();
    }while(isalnum(c));

    fileReader.rewind();

    if (keyWords.find(buffer) != keyWords.end()) {
        tokenPtr = std::make_unique<Token>(keyWords.find(buffer)->second, buffer, line, posInLine);
        return std::make_unique<Token>(keyWords.find(buffer)->second, buffer, line, posInLine);
    } else {
        tokenPtr = std::make_unique<Token>(Type::IDENTIFIER, buffer, line, posInLine);
        return std::make_unique<Token>(Type::IDENTIFIER, buffer, line, posInLine);
    }
}

std::unique_ptr<Token> Lexer::createString(unsigned int line, unsigned int posInLine) {
    std::cout<<"createString"<<std::endl;
    auto c = this->fileReader.getSign();
    std::string buffer;
    do {
        buffer.push_back(c);
        c = this->fileReader.getNextChar();
        if(c != '\'' && c != '\n' && !isEndOfFile()){
            buffer.push_back(c);
        }
        else if(c =='\n' || fileReader.isEndOfFile()){
            tokenPtr = std::make_unique<Token>(Type::ERROR, "Error", line, posInLine);
            handleError(tokenPtr->line, tokenPtr->positionInLine, "You forgotten to close the string. ");
            return std::make_unique<Token>(Type::ERROR, "Error", line, posInLine);
        }
        else if(c == '\'') {
            tokenPtr = std::make_unique<Token>(Type::STRING, buffer, line, posInLine);
            return std::make_unique<Token>(Type::STRING, buffer, line, posInLine);
        }
    }while(1);
}

std::unique_ptr<Token> Lexer::createSignToken(unsigned int line, unsigned int posInLine){
    std::cout<<"createTokenSign"<<std::endl;
    auto c = fileReader.getSign();
    auto nextChar = 0;
    std::cout<<"********przed switch"<<std::endl;
    switch (c) {
        case '&' :
            if (this->fileReader.getNextChar() == '&') {
                tokenPtr = std::make_unique<Token>(Type::AND, "&&", line, posInLine);
                return std::make_unique<Token>(Type::AND, "&&", line, posInLine);
            } else {
                this->fileReader.rewind();
                tokenPtr = std::make_unique<Token>(Type::ERROR, "Error", line, posInLine);
                handleError(tokenPtr->line, tokenPtr->positionInLine, "Unexpected symbol."); // TODO
                return std::make_unique<Token>(Type::ERROR, "Error", line, posInLine);
            }

        case '|':
            if (this->fileReader.getNextChar() == '|') {
                tokenPtr = std::make_unique<Token>(Type::OR, "||", line, posInLine);
                return std::make_unique<Token>(Type::OR, "||", line, posInLine);
            } else {
                this->fileReader.rewind();
                tokenPtr = std::make_unique<Token>(Type::ERROR, "Error", line, posInLine);
                handleError(tokenPtr->line, tokenPtr->positionInLine, "Unexpected symbol.");
                return std::make_unique<Token>(Type::ERROR, "Error", line, posInLine);
            }

        case '<':
            if (this->fileReader.getNextChar() == '=') {
                tokenPtr = std::make_unique<Token>(Type::LESS_EQUAL, "<=", line, posInLine);
                return std::make_unique<Token>(Type::LESS_EQUAL, "<=", line, posInLine);
            } else {
                this->fileReader.rewind();
                tokenPtr = std::make_unique<Token>(Type::LESS, "<", line, posInLine);
                return std::make_unique<Token>(Type::LESS, "<", line, posInLine);
            }

        case '>':
            if (this->fileReader.getNextChar() == '=') {
                tokenPtr = std::make_unique<Token>(Type::GREATER_EQUAL, ">=", line, posInLine);
                return std::make_unique<Token>(Type::GREATER_EQUAL, ">=", line, posInLine);
            } else {
                this->fileReader.rewind();
                tokenPtr = std::make_unique<Token>(Type::GREATER, ">", line, posInLine);
                return std::make_unique<Token>(Type::GREATER, ">", line, posInLine);
            }

        case '=':
            if (this->fileReader.getNextChar() == '=') {
                tokenPtr = std::make_unique<Token>(Type::EQUAL, "==", line, posInLine);
                return std::make_unique<Token>(Type::EQUAL, "==", line, posInLine);
            } else {
                this->fileReader.rewind();
                tokenPtr = std::make_unique<Token>(Type::ASSIGNMENT, "=", line, posInLine);
                return std::make_unique<Token>(Type::ASSIGNMENT, "=", line, posInLine);
            }

        case '!':
            if (this->fileReader.getNextChar() == '=') {
                tokenPtr = std::make_unique<Token>(Type::BANG_EQUAL, "!=", line, posInLine);
                return std::make_unique<Token>(Type::BANG_EQUAL, "!=", line, posInLine);
            } else {
                this->fileReader.rewind();
                tokenPtr = std::make_unique<Token>(Type::ERROR, "Error", line, posInLine);
                handleError(tokenPtr->line, tokenPtr->positionInLine, "Unexpected symbol.");
                return std::make_unique<Token>(Type::ERROR, "Error", line, posInLine);
            }

        case '+':
            nextChar = this->fileReader.getNextChar();
            if (nextChar == '+') {
                tokenPtr = std::make_unique<Token>(Type::INCREMENTATION, "++", line, posInLine);
                return std::make_unique<Token>(Type::INCREMENTATION, "++", line, posInLine);
            } else if (nextChar == '=') {
                tokenPtr = std::make_unique<Token>(Type::PLUS_EQUAL, "+=", line, posInLine);
                return std::make_unique<Token>(Type::PLUS_EQUAL, "+=", line, posInLine);
            } else {
                this->fileReader.rewind();
                tokenPtr = std::make_unique<Token>(Type::PLUS, "+", line, posInLine);
                return std::make_unique<Token>(Type::PLUS, "+", line, posInLine);
            }

        case '-':
            nextChar = this->fileReader.getNextChar();
            if (nextChar == '-') {
                tokenPtr = std::make_unique<Token>(Type::DECREMENTATION, "--", line, posInLine);
                return std::make_unique<Token>(Type::DECREMENTATION, "--", line, posInLine);
            } else if (nextChar == '=') {
                tokenPtr = std::make_unique<Token>(Type::MINUS_EQUAL, "-=", line, posInLine);
                return std::make_unique<Token>(Type::MINUS_EQUAL, "-=", line, posInLine);
            } else {
                this->fileReader.rewind();
                tokenPtr = std::make_unique<Token>(Type::MINUS, "-", line, posInLine);
                return std::make_unique<Token>(Type::MINUS, "-", line, posInLine);
            }
        case '\'':
            createString(line, posInLine);
            break;
        default: {
            std::cout<<"*****default"<<std::endl;
            if (singleSigns.find(c) != singleSigns.end()) {
                tokenPtr = std::make_unique<Token>(singleSigns.at(c), std::string(1,c), line, posInLine);
                return std::make_unique<Token>(singleSigns.at(c), std::string(1,c), line, posInLine);
            } else {
                tokenPtr = std::make_unique<Token>(Type::ERROR, "Error", line, posInLine);
                handleError(tokenPtr->line, tokenPtr->positionInLine, "Unexpected symbol.");
                return std::make_unique<Token>(Type::ERROR, "Error", line, posInLine);
            }
        }
    }
}

Token Lexer::nextToken() {
    //std::cout<<"**********next token"<<std::endl;

    skipUnrelevant();

    auto c = fileReader.getSign();
    std::cout<<"c: "<<c<<std::endl;
    std::cout<<"line: "<<fileReader.getLineNumber()<<std::endl;
    std::cout<<"pos: "<<fileReader.getCurrentSignPos()<<std::endl;

    unsigned int line = fileReader.getLineNumber();
    unsigned int posInLine = fileReader.getCurrentSignPos();

    if (c == EOF) { createEndOfFile(line, posInLine); }

    else if (isdigit(c))
        createDigit(line, posInLine);
    else if (isalpha(c))
        createIdentifier(line, posInLine);
    else createSignToken(line, posInLine);

    std::cout<<"Type: "<<typeNames.at(tokenPtr->type)/*<<" StringValue: "<<tokenPtr->stringValue*/<<" Line: "<<tokenPtr->line<<" Pos in Line: "<<tokenPtr->positionInLine<<std::endl;
}


