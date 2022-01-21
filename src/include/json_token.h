#ifndef JSON_TOKEN_H
#define JSON_TOKEN_H

typedef enum TOKEN_T {
    TOKEN_STRING,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_COMMA,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_ID,
    TOKEN_COLON
} token_enum_t;

typedef struct TOKEN_STRUCT {
    token_enum_t type;
    char *value;
} token_t;

token_t *new_token(int type, char *value);

void token_free(token_t *token);

#endif
