// author: Adela Jaworowska / index: 283747

#ifndef TKOM_LEXER_H
#define TKOM_LEXER_H
#include <string>
#include "Token.h"
#include "FileReader.h"
#include "ErrorHandler.h"


class Lexer {

private:
    FileReader fileReader;
    const Token handleError(const Token &token, std::string errorMsg);
    bool isEndOfFile();
    bool skipUnrelevant();
    bool createDigit();
    bool createString();
    bool createIdentifier();


public:
    Token *token; // last created token to take by parser
    Lexer(const std::string &fileName);
    Token nextToken();
};


#endif //TKOM_LEXER_H
