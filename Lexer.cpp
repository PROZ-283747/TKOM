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

// for testing purposes -> to delete
void printToken(const Token &token){
    std::cout<< "TOKEN: "<< " type: " << token.type << " value: \""<< token.value << "\" line:  " << token.line << " poss: " << token.positionInLine << std::endl;
}

Token Lexer::nextToken() {
    Token token; // token to return  // powołać dożycia kiedy już wiem ze jest, ze dałos ie zbudować; lekser ma trzymć token bo potem bedzie go pobierał parser
    // przy wejsciu do tej funkcji ma być znak już pobrany ale jeszecze nie przetworzony, a na wyjsciu on ma byc ustawiony na pierwszej pozycji tokenu
    auto sign= this->fileReader.getNextChar(); // Loads new character from file reader to analyze and to create token.
    char nextChar;

    while (isspace(sign)) // Skips all white characters (spaces).
    {
        // tu pomijać komentarze
        sign = this->fileReader.getNextChar();
        // zwracać true jesli pominięte
    }
    // sets the position of beginning of currently analyzed token
    token.line = this->fileReader.lineNumber;
    token.positionInLine = this->fileReader.currentSignPos - 1;

    // returns token EOF if it is end of file
    if (sign == EOF) {
        std::cout<<"end" <<std::endl;
        token.type = Type::END_OF_FILE;
        token.value = "EndOfFile";
        printToken(token);
        return token; // tu tworzyć token - konstruktorem
    }

    if(isalpha(sign)){
        // to mozna obudować w funkcje gdy sign bedzie w Readerze
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
        fileReader.rewind();
    }

    else if(isdigit(sign)){
        // funkcja
        // TODO: spróbuj zbudować()
        // lub tabela ze znakami z podpiętymi funkcjami spróbuj()
        std::string buffer;
        do
        {
            buffer.push_back(sign);
            sign = this->fileReader.getNextChar();
        } while (isdigit(sign));
        if(sign == '%' && isdigit(fileReader.getPeek())) {
            buffer.push_back(sign);
            sign = this->fileReader.getNextChar();
        }
        do{
            buffer.push_back(sign);
            sign = this->fileReader.getNextChar();
        }
        while(isdigit(sign));
        fileReader.rewind();
        token.type = Type::NUMBER;
        token.value = buffer;
    }
    else {
        switch (sign) {
            case ' ' :

            case '\r' : // chyba liczone jako białe znaki

            case '\t' :
                break;

            case '\n' :
                ++token.line;
                break;

//            case '#' : { // można pomijać, obsługiwać tm gdzie białe znaki
//                std::string buffer;
//                token.type = Type::COMMENT;
//                do {
//                    buffer.push_back(sign);
//                    sign = this->fileReader.getNextChar();
//                } while (sign != '\n');
//
//                token.value = buffer;
//                this->fileReader.rewind();
//                break;
//            }
            case'\'' :
            {
                //funkcja
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
                // jak dołączłam do tokena to pobieram kolejny w readerze a jak nie to zostaje
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
                //std::cout<<"default: " <<std::endl;
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

    printToken(token);
    return token;


}

