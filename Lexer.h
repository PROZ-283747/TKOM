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
public:
    Lexer(const std::string &fileName);
    Token nextToken();
};


#endif //TKOM_LEXER_H
