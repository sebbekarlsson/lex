#ifndef LEX_LEX_H
#define LEX_LEX_H
#include "token.h"


typedef struct {
    char* buffer;
    char current_char;
    int pos;
} lex_state;


lex_state* lex_init();

token* lex_get_next_token(lex_state* state);

#endif
