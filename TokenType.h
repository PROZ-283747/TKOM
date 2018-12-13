// author: Adela Jaworowska / index: 283747

#ifndef TKOM_TYPE_H
#define TKOM_TYPE_H

#include <unordered_map>
namespace token {

    enum Type
    {
        // Single character tokens
                LEFT_PARENTHESIS,   //"{"
        RIGHT_PARENTHESIS,  //"}"
        LEFT_BRACKET,       //"("
        RIGHT_BRACKET,      //")"
        COMMA,              //","
        COLON,              //":"
        SEMICOLON,          //";"
        APOSTROPHE,         //"'"
        SLASH,              //"/"
        STAR,               //"*"
        HASH,                //"#"

        // One or two characters tokens
                PLUS,               //"+"
        INCREMENTATION,     //"++"
        MINUS,              //"-"
        DECREMENTATION,     //"--"
        MINUS_EQUAL,        //"-="
        PLUS_EQUAL,         //"+="
        BANG_EQUAL,         //"!="
        ASSIGNMENT,         //"="
        EQUAL,              //"=="
        GREATER,            //">"
        GREATER_EQUAL,      //">="
        LESS,               //"<"
        LESS_EQUAL,         //"<="
        AND,                //"&&"
        OR,                 //"||"

        // Keywords
                FRACTION_T,         //"fraction"
        STRING_T,           // "string"
        VOID_T,             // "void"
        ELSE,               // "else"
        FOR,                // "for"
        IF,                 // "if"
        WHILE,              // "while"
        RETURN,             // "return"

        // Literals
                IDENTIFIER,         // eg. "myVariable"
        STRING,             // eg. "'Example of string'"
        NUMBER,             // eg. 5%7, 18%1, 45
        COMMENT,            // eg. # This is a comment

        // End of file
                END_OF_FILE,        // EOF

        // When error
                ERROR        // sth incorrect

    };


    // keywords defined in my own language
    const std::unordered_map<std::string, Type> keyWords = {

            {"fraction",         FRACTION_T},
            {"string",           STRING_T},
            {"void",             VOID_T},
            {"else",             ELSE},
            {"for",              FOR},
            {"if",               IF},
            {"while",            WHILE},
            {"return",           RETURN}
    };


    // symbols which can occur alone in a code
    const std::unordered_map<char, Type> singleSigns = {

            { '{', LEFT_PARENTHESIS},
            { '}', RIGHT_PARENTHESIS},
            { '(', LEFT_BRACKET },
            { ')', RIGHT_BRACKET},
            { ',', COMMA},
            { ':', COLON},
            { ';', SEMICOLON },
            { '/', APOSTROPHE },
            { '*', STAR},
            { '/', SLASH },
            { '#', HASH}
    };



}
#endif //TKOM_TYPE_H

