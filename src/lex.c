#include "includes/lex.h"
#include "includes/strutils.h"
#include <stdlib.h>
#include <stdio.h>


lex_state* lex_init(char* buffer) {
    lex_state* state;
    state = malloc(sizeof(state));
    state->buffer = buffer;
    state->pos = 0;
    state->current_char = state->buffer[state->pos];

    return state;
}

void lex_advance(lex_state* state) {
    if (state->buffer[state->pos] != '\0') {
        state->pos += 1;
        state->current_char = state->buffer[state->pos];
    }
};

token* lex_get_next_token(lex_state* state) {
    char* str = char_to_string(state->current_char); 

    if (state->current_char == '\0')
        return init_token(_EOF, str);

    token* tok;

    if (state->current_char == '+')
        tok = init_token(_OP_PLUS, str);
    else
        tok = init_token(_STRING, str);

    lex_advance(state);

    return tok;
}
