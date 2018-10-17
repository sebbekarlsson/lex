#include <stdio.h>
#include <stdlib.h>
#include "includes/lex.h"


int main(int argc, char* argv[]) {
    lex_state* state = lex_init("x = 1 + 2 + 999.5 + 300 + 2 + 5.5 + 0.5");
    token* tok; 

    while (1) {
        tok = lex_get_next_token(state);

        if (tok->type == _EOF) {
            free(tok);
            break;
        }

        printf("Token(%d, %s)\n", tok->type, tok->value);

        free(tok->value);
        free(tok);
    }

    free(state);

    return 0;
};
