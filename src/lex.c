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

/**
 * Moves the cursor / position to the next position.
 *
 * @param lex_state* state
 */
void lex_advance(lex_state* state) {
    if (state->buffer[state->pos] != '\0') {
        state->pos += 1;
        state->current_char = state->buffer[state->pos];
    }
};

/**
 * Get the next token based on the position and the buffer
 *
 * @param lex_state* state
 */
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

        if (state->current_char == '-') {
            lex_advance(state);
            return init_token(_OP_SUBTRACT, str);
        }

        if (state->current_char == '/') {
            lex_advance(state);
            return init_token(_OP_DIVIDE, str);
        }

        if (state->current_char == '*') {
            lex_advance(state);
            return init_token(_OP_MULTIPLY, str);
        }

        if (state->current_char == '(') {
            lex_advance(state);
            return init_token(_LPAREN, str);
        }

        if (state->current_char == ')') {
            lex_advance(state);
            return init_token(_RPAREN, str);
        }

        if (state->current_char == '{') {
            lex_advance(state);
            return init_token(_LBRACE, str);
        }

        if (state->current_char == '}') {
            lex_advance(state);
            return init_token(_RBRACE, str);
        }

        if (state->current_char == ';') {
            lex_advance(state);
            return init_token(_SEMI, str);
        }

        if (state->current_char == '"') {
            free(str);
            return init_token(_STRING, lex_parse_string(state));
        }

        if (isdigit(state->current_char)) {
            free(str);
            return init_token(_INTEGER, lex_parse_number(state));
        }

        if (isalnum(state->current_char)) {
            free(str);
            return init_token(_ID, lex_parse_id(state));
        }

        free(str);
        lex_advance(state);
    }

    return init_token(_EOF, "");
};

/**
 * Used to skip white space until we get to a interesting char.
 *
 * @param lex_state* state
 */
void lex_skip_whitespace(lex_state* state) {
    lex_advance(state);

    while (state->current_char == ' ' && state->current_char != '\0')
        lex_advance(state);
};

/**
 * Parses an ID, this is quite vague but it is chunks of string which is
 * alpha numerical.
 *
 * @param lex_state* state
 */
char* lex_parse_id(lex_state* state) {
    char* buff;
    char* charstr;

    buff = calloc(2, sizeof(char*));
    charstr = char_to_string(state->current_char);
    strcat(buff, charstr);
    lex_advance(state);
    free(charstr);

    while (isalnum(state->current_char)) {
        buff = realloc(buff, sizeof(buff) + (sizeof(char) * 2));
        charstr = char_to_string(state->current_char);
        strcat(buff, charstr);
        lex_advance(state);
        free(charstr);
    }

    return buff;
};

/**
 * Parses a number, basically a piece of string which is completely
 * numerical
 *
 * @param lex_state* state
 */
char* lex_parse_number(lex_state* state) {
    char* buff;
    char* charstr;

    buff = calloc(2, sizeof(char*));
    charstr = char_to_string(state->current_char);
    strcat(buff, charstr);
    lex_advance(state);
    free(charstr);

    while (isdigit(state->current_char)) {
        buff = realloc(buff, sizeof(buff) + (sizeof(char) * 2));
        charstr = char_to_string(state->current_char);
        strcat(buff, charstr);
        lex_advance(state);
        free(charstr);
    }

    // float
    if (state->current_char == '.') {
        buff = realloc(buff, sizeof(buff) + (sizeof(char) * 2));
        charstr = char_to_string(state->current_char);
        strcat(buff, charstr);
        lex_advance(state);

        while (isdigit(state->current_char)) {
            buff = realloc(buff, sizeof(buff) + (sizeof(char) * 2));
            charstr = char_to_string(state->current_char);
            strcat(buff, charstr);
            lex_advance(state);
        }

        free(charstr);
    }

    return buff;
}

/**
 * Capture everything between `"`
 *
 * @param lex_state*
 *
 * @return char*
 */
char* lex_parse_string(lex_state* state) {
    lex_advance(state);

    char* buff;
    char* charstr;

    buff = calloc(2, sizeof(char*));
    charstr = char_to_string(state->current_char);
    strcat(buff, charstr);
    lex_advance(state);
    free(charstr);

    while (state->current_char != '\0') {
        if (state->current_char == '"')
            break;

        buff = realloc(buff, strlen(buff) + (sizeof(char) * 2));
        charstr = char_to_string(state->current_char);
        strcat(buff, charstr);
        lex_advance(state);
        free(charstr);
    }

    lex_advance(state);

    return buff;
}
