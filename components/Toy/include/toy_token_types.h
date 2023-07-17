#ifndef TOY_TOKEN_TYPES_H_
#define TOY_TOKEN_TYPES_H_

typedef enum Toy_TokenType {
    //types
    TOY_TOKEN_NULL, //
    TOY_TOKEN_BOOLEAN, //
    TOY_TOKEN_INTEGER, //
    TOY_TOKEN_FLOAT, //
    TOY_TOKEN_STRING, //
    TOY_TOKEN_ARRAY, //
    TOY_TOKEN_DICTIONARY, //
    TOY_TOKEN_FUNCTION, //
    TOY_TOKEN_OPAQUE, //
    TOY_TOKEN_ANY, //

    //keywords and reserved words
    TOY_TOKEN_AS, //
    TOY_TOKEN_ASSERT, //
    TOY_TOKEN_BREAK, //
    TOY_TOKEN_CLASS, //
    TOY_TOKEN_CONST, //
    TOY_TOKEN_CONTINUE, //
    TOY_TOKEN_DO, //
    TOY_TOKEN_ELSE, //
    TOY_TOKEN_EXPORT, //
    TOY_TOKEN_FOR, //
    TOY_TOKEN_FOREACH, //
    TOY_TOKEN_IF, //
    TOY_TOKEN_IMPORT, //
    TOY_TOKEN_IN, //
    TOY_TOKEN_OF, //
    TOY_TOKEN_PRINT, //
    TOY_TOKEN_RETURN, //
    TOY_TOKEN_TYPE, //
    TOY_TOKEN_ASTYPE, //
    TOY_TOKEN_TYPEOF, //
    TOY_TOKEN_VAR, //
    TOY_TOKEN_WHILE, //

    //literal values
    TOY_TOKEN_IDENTIFIER, //
    TOY_TOKEN_LITERAL_TRUE, //
    TOY_TOKEN_LITERAL_FALSE, //
    TOY_TOKEN_LITERAL_INTEGER, //
    TOY_TOKEN_LITERAL_FLOAT, //
    TOY_TOKEN_LITERAL_STRING, //

    //math operators
    TOY_TOKEN_PLUS, //
    TOY_TOKEN_MINUS, //
    TOY_TOKEN_MULTIPLY, //
    TOY_TOKEN_DIVIDE, //
    TOY_TOKEN_MODULO, //
    TOY_TOKEN_PLUS_ASSIGN, //
    TOY_TOKEN_MINUS_ASSIGN, //
    TOY_TOKEN_MULTIPLY_ASSIGN, //
    TOY_TOKEN_DIVIDE_ASSIGN, //
    TOY_TOKEN_MODULO_ASSIGN, //
    TOY_TOKEN_PLUS_PLUS, //
    TOY_TOKEN_MINUS_MINUS, //
    TOY_TOKEN_ASSIGN, //

    //logical operators
    TOY_TOKEN_PAREN_LEFT, //
    TOY_TOKEN_PAREN_RIGHT, //
    TOY_TOKEN_BRACKET_LEFT, //
    TOY_TOKEN_BRACKET_RIGHT, //
    TOY_TOKEN_BRACE_LEFT, //
    TOY_TOKEN_BRACE_RIGHT, //
    TOY_TOKEN_NOT, //
    TOY_TOKEN_NOT_EQUAL, //
    TOY_TOKEN_EQUAL, //
    TOY_TOKEN_LESS, //
    TOY_TOKEN_GREATER, //
    TOY_TOKEN_LESS_EQUAL, //
    TOY_TOKEN_GREATER_EQUAL, //
    TOY_TOKEN_AND, //
    TOY_TOKEN_OR, //

    //other operators
    TOY_TOKEN_QUESTION, //
    TOY_TOKEN_COLON, //
    TOY_TOKEN_SEMICOLON, //
    TOY_TOKEN_COMMA, //
    TOY_TOKEN_DOT, //
    TOY_TOKEN_PIPE, //
    TOY_TOKEN_REST, //

    //meta tokens
    TOY_TOKEN_PASS, //
    TOY_TOKEN_ERROR, //
    TOY_TOKEN_EOF, //
} Toy_TokenType;

#endif /* TOY_TOKEN_TYPES_H_ */
