#ifndef LEX_TOKEN_TYPE_H
#define LEX_TOKEN_TYPE_H
typedef enum {
    _EOF = 0,
    _ID = 1,
    _INTEGER = 2,
    _STRING = 3,
    _OP_PLUS = 4
} tokentype;
#endif
