// author: Adela Jaworowska / index: 283747

#ifndef TKOM_TYPE_H
#define TKOM_TYPE_H

#include <unordered_map>
namespace token {

    enum Type : unsigned int
    {
        // Single character tokens
        LEFT_PARENTHESIS = 0,   //"{"
        RIGHT_PARENTHESIS = 1,  //"}"
        LEFT_BRACKET = 2,       //"("
        RIGHT_BRACKET = 3,      //")"
        LEFT_SQUARE_BRACKET = 4,//"["
        RIGHT_SQUARE_BRACKET=5, //"]"
        COMMA = 6,              //","
        COLON = 7,              //":"
        SEMICOLON = 8,          //";"
        APOSTROPHE = 9,         //"'"
        SLASH = 10,             //"/"
        STAR = 11,              //"*"
        HASH =12,               //"#"

        // One or two characters tokens
        PLUS = 13,               //"+"
        INCREMENTATION = 14,     //"++"
        MINUS = 15,              //"-"
        DECREMENTATION = 16,     //"--"
        MINUS_EQUAL = 17,        //"-="
        PLUS_EQUAL = 18,         //"+="
        BANG_EQUAL = 19,         //"!="
        ASSIGNMENT = 20,         //"="
        EQUAL = 21,              //"=="
        GREATER = 22,            //">"
        GREATER_EQUAL = 23,      //">="
        LESS = 24,               //"<"
        LESS_EQUAL = 25,         //"<="
        AND = 26,                //"&&"
        OR = 27,                 //"||"

        // Keywords
        FRACTION_T = 28,         //"fraction"
        STRING_T = 29,           // "string"
        VOID_T = 30,             // "void"
        ELSE = 31,               // "else"
        FOR = 32,                // "for"
        IF = 33,                 // "if"
        WHILE = 34,              // "while"
        RETURN = 35,             // "return"

        // Literals
        IDENTIFIER = 36,         // eg. "myVariable"
        STRING = 37,             // eg. "'Example of string'"
        NUMBER = 38,             // eg. 5%7, 18%1, 45

        // End of file
        END_OF_FILE = 39,        // EOF

        // When error
        ERROR = 40               // sth incorrect
    };


    const std::unordered_map<unsigned int, std::string> typeNames = {
            {0, "LEFT_PARENTHESIS"},
            {1, "RIGHT_PARENTHESIS"},
            {2, "LEFT_BRACKET"},
            {3, "RIGHT_BRACKET"},
            {4, "RIGHT_SQUARE_BRACKET"},
            {5, "LEFT_SQUARE_BRACKET"},
            {6, "COMMA"},
            {7, "COLON"},
            {8, "SEMICOLON"},
            {9, "APOSTROPHE"},
            {10, "SLASH"},
            {11, "STAR"},
            {12, "HASH"},
            {13, "PLUS"},
            {14, "INCREMENTATION"},
            {15, "MINUS"},
            {16, "DECREMENTATION"},
            {17, "MINUS_EQUAL"},
            {18, "PLUS_EQUAL"},
            {19, "BANG_EQUAL"},
            {20, "ASSIGNMENT"},
            {21, "EQUAL"},
            {22, "GREATER"},
            {23, "GREATER_EQUAL"},
            {24, "LESS"},
            {25, "LESS_EQUAL"},
            {26, "AND"},
            {27, "OR"},
            {28, "FRACTION_T"},
            {29, "STRING_T"},
            {30, "VOID_T"},
            {31, "ELSE"},
            {32, "FOR"},
            {33, "IF"},
            {34, "WHILE"},
            {35, "RETURN"},
            {36, "IDENTIFIER"},
            {37, "STRING"},
            {38, "NUMBER"},
            {39, "END_OF_FILE"},
            {40, "ERROR"}
    };

    // keywords defined in my own language
    const std::unordered_map<std::string, Type> keyWords = {
            {"fraction", FRACTION_T},
            {"string", STRING_T},
            {"void", VOID_T},
            {"else", ELSE},
            {"for", FOR},
            {"if", IF},
            {"while", WHILE},
            {"return", RETURN}
    };

    // symbols which can occur alone in a code
    const std::unordered_map<char, Type> singleSigns = {

            { '{', LEFT_PARENTHESIS},
            { '}', RIGHT_PARENTHESIS },
            { '(', LEFT_BRACKET },
            { ')', RIGHT_BRACKET },
            { '[', LEFT_SQUARE_BRACKET },
            { ']', RIGHT_SQUARE_BRACKET },
            { ',', COMMA },
            { ':', COLON },
            { ';', SEMICOLON },
            { '\'', APOSTROPHE },
            { '/', SLASH },
            { '*', STAR },
            { '#', HASH }
    };

    inline const std::string getTypeName(const Type& tokenType)
    {
        return typeNames.at(static_cast<unsigned int>(tokenType));
    };



}
#endif //TKOM_TYPE_H

