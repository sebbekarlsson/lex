#ifndef LEX_TOKEN_TYPE_H
#define LEX_TOKEN_TYPE_H
typedef enum {
    _EOF = 0,
    _ID,
    _INTEGER,
    _STRING,
    _OP_PLUS,
    _OP_SUBTRACT,
    _OP_MULTIPLY,
    _OP_DIVIDE,
    _OP_MOD,
    _OP_PERCENTAGE,
    _LPAREN,
    _RPAREN,
    _LBRACE,
    _RBRACE,
    _RETURN,
    _IF,
    _ELSE,
    _SEMI
} tokentype;
#endif
