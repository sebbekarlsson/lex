#include "includes/lex.h"
#include "includes/strutils.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>


lex_state* lex_init(char* buffer) {
    lex_state* state;
    state = malloc(sizeof(struct LEX_STATE_STRUCT));
    state->buffer = buffer;
    state->pos = 0;
    state->current_char = state->buffer[state->pos];

    return state;
};

void lex_advance(lex_state* state) {
    if (state->buffer[state->pos] != '\0') {
        state->pos += 1;
        state->current_char = state->buffer[state->pos];
    }
};

token* lex_get_next_token(lex_state* state) {
    while (state->current_char != '\0') {
        char* str = char_to_string(state->current_char); 

        if (state->current_char == '\0') {
            return init_token(_EOF, str);
        }

        if (state->current_char == ' ') {
            lex_skip_whitespace(state);
            free(str);
            continue;
        }

        if (state->current_char == '+') {
            lex_advance(state);
            return init_token(_OP_PLUS, str);
        }

        if (isdigit(state->current_char)) {
            return init_token(_INTEGER, lex_parse_number(state));
        }

        if (isalnum(state->current_char)) {
            return init_token(_ID, lex_parse_id(state));
        }

        free(str);
        lex_advance(state);
    }

    return init_token(_EOF, "");
};

void lex_skip_whitespace(lex_state* state) {
    lex_advance(state);

    while (state->current_char == ' ' && state->current_char != '\0')
        lex_advance(state);
};

char* lex_parse_id(lex_state* state) {
    char* buff;
    buff = malloc(sizeof(char) * 2);
    buff[0] = state->current_char;
    buff[1] = '\0';

    lex_advance(state);

    while (isalnum(state->current_char)) {
        buff = malloc(strlen(buff)+1);
        buff[sizeof(buff)] = state->current_char;
        buff[sizeof(buff)+1] = '\0';
        lex_advance(state);
    }

    return buff;
};

char* lex_parse_number(lex_state* state) {
    char* buff;
    buff = malloc(sizeof(char) * 2);
    buff[0] = state->current_char;
    buff[1] = '\0';
    
    lex_advance(state);

    while (isdigit(state->current_char)) {
        buff = realloc(buff, sizeof(buff) + (sizeof(char) * 2));
        buff[strlen(buff)] = state->current_char;
        buff[strlen(buff)] = '\0';
        lex_advance(state);
    }

    // float
    if (state->current_char == '.') {
        buff = realloc(buff, sizeof(buff) + (sizeof(char) * 2));
        buff[strlen(buff)] = state->current_char;
        buff[strlen(buff)] = '\0';
        lex_advance(state);

        while (isdigit(state->current_char)) {
            buff = realloc(buff, sizeof(buff) + (sizeof(char) * 2));
            buff[strlen(buff)] = state->current_char;
            buff[strlen(buff)] = '\0';
            lex_advance(state);
        }
    }

    return buff;
}
