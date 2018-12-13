// author: Adela Jaworowska / index: 283747

#include <winnt.h>
#include "Lexer.h"
#include "ErrorHandler.h"


Lexer::Lexer(const std::string &fileName) : fileReader(fileName){}

const Token Lexer::handleError(const Token &token, std::string errorMsg) {
    ErrorHandler errorHandler;
    errorHandler.printError("LEXER", token, errorMsg);
    return this->nextToken();
}

Token Lexer::nextToken() {
    Token token; // token to return

    auto sign= this->fileReader.getNextChar(); // Loads new character from file reader to analyze and to create token.
    char nextChar;

    while (isspace(sign)) // Skips all white characters (spaces).
    {
        sign = this->fileReader.getNextChar();
    }
    // sets the position of beginning of currently analyzed token
    token.line = this->fileReader.lineNumber;
    token.positionInLine = this->fileReader.currentSignPos - 1;

    // returns token EOF if it is end of file
    if (this->fileReader.isEndOfFile()) {
        token.type = Type::END_OF_FILE;
        token.value = "EndOfFile";
        token.printToken();
        return token;
    }

    if(isalpha(sign)){
        std::string buffer;

        do{
            buffer.push_back(sign);
            sign = this->fileReader.getNextChar();
        }while(isalnum(sign));

        if (keyWords.find(buffer) != keyWords.end()) {
            token.type = keyWords.find(buffer)->second;
            token.value = buffer;
        } else {
            token.type = Type::IDENTIFIER;
            token.value = buffer;
        }
    }

    else if(isdigit(sign)){
        std::string buffer;
        do
        {
            buffer.push_back(sign);
            sign = this->fileReader.getNextChar();
        } while (isdigit(sign));
        if(sign == '%' && isdigit(fileReader.getPeek())){
            do{
                buffer.push_back(sign);
                sign = this->fileReader.getNextChar();
            }
            while(isdigit(sign));
            this->fileReader.rewind();
        }
        token.type = Type::NUMBER;
        token.value = buffer;
    }
    else {
        switch (sign) {
            case ' ' :

            case '\r' :

            case '\t' :
                break;

            case '\n' :
                ++token.line;
                break;

            case '#' : {
                std::string buffer;
                token.type = Type::COMMENT;
                do {
                    buffer.push_back(sign);
                    sign = this->fileReader.getNextChar();
                } while (sign != '\n');

                token.value = buffer;
                this->fileReader.rewind();
                break;
            }
            case'\'' :
            {
                std::string buffer;
                token.type = Type::STRING;
                do {
                    sign = this->fileReader.getNextChar();
                    if(sign != '\'' && sign != '\n' && !fileReader.isEndOfFile()){
                        buffer.push_back(sign);
                    }
                    else if(sign =='\n' || fileReader.isEndOfFile()){
                        token.type = Type::ERROR;
                        token = handleError(token,"You forgotten to close the string. ");
                        break;
                    }
                    else if(sign== '\'') {
                        token.type = Type::STRING;
                        token.value = buffer;
                        break;
                    }
                }while(1);
                break;
            }
            case '&' :
                if (this->fileReader.getNextChar() == '&') {
                    token.type = Type::AND;
                    token.value = "&&";
                }
                else {
                    this->fileReader.rewind();
                    token.type = Type::ERROR;
                    token = handleError( token, "Unexpected symbol. ");
                }
                break;
            case '|':
                if (this->fileReader.getNextChar() == '|') {
                    token.type = Type::OR;
                    token.value = "||";
                }
                else
                {
                    this->fileReader.rewind();
                    token.type = Type::ERROR;
                    token = handleError(token, "Unexpected symbol. ");
                }
                break;
            case '<':
                if (this->fileReader.getNextChar() == '=') {
                    token.type = Type::LESS_EQUAL;
                    token.value = "<=";
                }
                else {
                    this->fileReader.rewind();
                    token.type = Type::LESS;
                    token.value = "<";
                }
                break;

            case '>':
                if (this->fileReader.getNextChar() == '=') {
                    token.type = Type::GREATER_EQUAL;
                    token.value = ">=";
                }
                else {
                    this->fileReader.rewind();
                    token.type = Type::GREATER;
                    token.value = ">";
                }
                break;

            case '=':
                if (this->fileReader.getNextChar() == '=') {
                    token.type = Type::EQUAL;
                    token.value = "==";
                }
                else {
                    this->fileReader.rewind();
                    token.type = Type::ASSIGNMENT;
                    token.value = "=";
                }
                break;

            case '!':
                if (this->fileReader.getNextChar() == '=') {
                    token.type = Type::BANG_EQUAL;
                    token.value = "!=";
                }
                else {
                    this->fileReader.rewind();
                    token.type = Type::ERROR;
                    token = handleError(token, "Unexpected symbol. ");
                }
                break;

            case '+':
                nextChar = this->fileReader.getNextChar();
                if (nextChar == '+') {
                    token.type = Type::INCREMENTATION;
                    token.value = "++";
                }
                else if(nextChar == '=') {
                    token.type = Type::PLUS_EQUAL;
                    token.value = "+=";
                }
                else {
                    this->fileReader.rewind();
                    token.type = Type::PLUS;
                    token.value = "+";
                }
                break;

            case '-':
                nextChar = this->fileReader.getNextChar();
                if (nextChar == '-') {
                    token.type = Type::DECREMENTATION;
                    token.value;
                }
                else if (nextChar == '=') {
                    token.type = Type::MINUS_EQUAL;
                    token.value;
                }
                else {
                    this->fileReader.rewind();
                    token.type = Type::MINUS;
                    token.value = "-";
                }
                break;

            default:
            {
                if (singleSigns.find(sign) != singleSigns.end()) {
                    token.type = singleSigns.at(sign);
                    token.value = sign;
                }
                else
                {
                    token.type = Type::ERROR;
                    token = handleError(token, "Unexpected symbol. ");
                }
            }
        }
    }

    token.printToken();
    return token;


}

