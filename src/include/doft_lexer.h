#ifndef DOFT_LEXER_H
#define DOFT_LEXER_H

#include <ctype.h>
#include "doft_token.h"

typedef struct LEXER_STRUCT {
    char *contents;
    int i;
    char c;
} lexer_t;

#define DOFT_EXTENSION ".doft"

lexer_t *new_lexer(char *contents);

void lexer_free(lexer_t *lexer);

char *lexer_read_file(const char *filename);

token_t *lexer_get_next_token(lexer_t *lexer);

token_t *lexer_advance_with_token(lexer_t *lexer, token_t *token);

void lexer_advance(lexer_t *lexer);

void lexer_skip_whitespace(lexer_t *lexer);

token_t *lexer_collect_number(lexer_t *lexer);

token_t *lexer_collect_id(lexer_t *lexer);

token_t *lexer_collect_string(lexer_t *lexer);

char *lexer_get_curr_char(lexer_t *lexer);

char lexer_peek(lexer_t *lexer);

#endif
