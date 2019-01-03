// author: Adela Jaworowska / index: 283747

#ifndef TKOM_LEXER_H
#define TKOM_LEXER_H
#include <string>
#include <memory>
#include "Token.h"
#include "FileReader.h"
#include "ErrorHandler.h"


class Lexer {

private:
    FileReader fileReader;
    const void handleError(unsigned int line, unsigned int pos, std::string errorMsg);
    bool isEndOfFile();
    void skipUnrelevant();
    std::unique_ptr<Token> createEndOfFile(unsigned int line, unsigned int posInLine);
    std::unique_ptr<Token> createDigit(unsigned int line, unsigned int posInLine);
    std::unique_ptr<Token> createString(unsigned int line, unsigned int posInLine);
    std::unique_ptr<Token> createIdentifier(unsigned int line, unsigned int posInLine);
    std::unique_ptr<Token> createSignToken(unsigned int line, unsigned int posInLine);


public:
    std::unique_ptr<Token> tokenPtr; // pointer last created token to take by parser
    Lexer(const std::string &fileName);
    Token nextToken();
    //void printToken(std::unique_ptr<Token> const &token);

    std::unique_ptr<Token> TokenFactory(Type type, std::string value, unsigned int line, unsigned int posLine)
    {
        // Implicit move operation into the variable that stores the result.
        return std::make_unique<Token>(type, value, line,posLine);
    }
};


#endif //TKOM_LEXER_H
