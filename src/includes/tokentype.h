#ifndef LEX_TOKEN_TYPE_H
#define LEX_TOKEN_TYPE_H
typedef enum {
    _EOF = 0,
    _ID = 1,
    _INTEGER = 2,
    _STRING = 3,
    _OP_PLUS = 4,
    _OP_SUBTRACT = 5,
    _OP_MULTIPLY = 6,
    _OP_DIVIDE = 7,
    _OP_MOD = 8,
    _OP_PERCENTAGE = 9,
    _LPAREN = 10,
    _RPAREN = 11,
    _LBRACE = 12,
    _RBRACE = 13,
    _RETURN = 14,
    _IF = 15,
    _ELSE = 16,
    _SEMI = 17
} tokentype;
#endif
