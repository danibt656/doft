#include <stdio.h>
#include <stdlib.h>

#include "include/json_token.h"


token_t *new_token(int type, char *value)
{
    token_t *new_token = malloc(sizeof(struct TOKEN_STRUCT));
    new_token->type = type;
    new_token->value = value;

    return new_token;
}

void token_free(token_t *token)
{
    if (token) {
        if (token->value)
            free(token->value);
        free(token);
    }
}
