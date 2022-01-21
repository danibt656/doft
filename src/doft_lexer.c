#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/doft_lexer.h"


lexer_t *new_lexer(char *contents)
{
    lexer_t *new_lexer = malloc(sizeof(struct LEXER_STRUCT));
    new_lexer->contents = contents;
    new_lexer->i = 0;
    new_lexer->c = contents[0];

    return new_lexer;
}

void lexer_free(lexer_t *lexer)
{
    if (lexer->contents)
        free(lexer->contents);
    free(lexer);
}

token_t *lexer_get_next_token(lexer_t *lexer)
{
    int len = strlen(lexer->contents);
    while (lexer->c != '\0' && lexer->i < len)
    {
        
        if (lexer->c == ' ' || lexer->c == 13 || lexer->c == 10 ||
            lexer->c == '\n' || lexer->c == '\r' || lexer->c == '\t')
            lexer_skip_whitespace(lexer);

        if (isdigit(lexer->c) || lexer->c == '-')
            return lexer_collect_number(lexer);

        if (isalnum(lexer->c))
            return lexer_collect_id(lexer);

        switch (lexer->c) {
            case '{' : return lexer_advance_with_token(lexer, new_token(TOKEN_LBRACE, lexer_get_curr_char(lexer))); break;
            case '}' : return lexer_advance_with_token(lexer, new_token(TOKEN_RBRACE, lexer_get_curr_char(lexer))); break;
            case '[' : return lexer_advance_with_token(lexer, new_token(TOKEN_LBRACKET, lexer_get_curr_char(lexer))); break;
            case ']' : return lexer_advance_with_token(lexer, new_token(TOKEN_RBRACKET, lexer_get_curr_char(lexer))); break;
            case ',' : return lexer_advance_with_token(lexer, new_token(TOKEN_COMMA, lexer_get_curr_char(lexer))); break;
            case ':' : return lexer_advance_with_token(lexer, new_token(TOKEN_COLON, lexer_get_curr_char(lexer))); break;
            case '"' : return lexer_advance_with_token(lexer, lexer_collect_string(lexer)); break;
            default: break;
        }

        if (lexer->c == 0)
            break;
        printf("[doft_lexer] Unexpected `%c`\n", lexer->c);
        exit(1);
    }
    return (void*)0;
}

token_t *lexer_advance_with_token(lexer_t *lexer, token_t *token)
{
    lexer_advance(lexer);
    return token;
}

void lexer_advance(lexer_t *lexer)
{
    if (lexer->i < strlen(lexer->contents)) {
        lexer->i += 1;
        lexer->c = lexer->contents[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_t *lexer)
{
    while (lexer->c == ' ' || lexer->c == 13 || lexer->c == 10 ||
            lexer->c == '\n' || lexer->c == '\r' || lexer->c == '\t')
        lexer_advance(lexer);
}

token_t *lexer_collect_number(lexer_t *lexer)
{
    char *value = malloc(sizeof(char));
    value[0] = '\0';
    int type = TOKEN_INT;

    if (lexer->c == '-') {
        char *str = lexer_get_curr_char(lexer);
        value = realloc(value, (strlen(value) + 1 + strlen(str)) * sizeof(char));
        strcat(value, str);
        free(str);
        lexer_advance(lexer);
    }

    while (isdigit(lexer->c)) {
        char *str = lexer_get_curr_char(lexer);
        value = realloc(value, (strlen(value) + 1 + strlen(str)) * sizeof(char));
        strcat(value, str);
        free(str);
        lexer_advance(lexer);
    }
    
    if (lexer->c == '.') {
        type = TOKEN_FLOAT;
        lexer_advance(lexer);
        
        while (isdigit(lexer->c)) {
            char *str = lexer_get_curr_char(lexer);
            strcat(value, str);
            free(str);
            lexer_advance(lexer);
        }
    }

    return new_token(type, value);
}

token_t *lexer_collect_id(lexer_t *lexer)
{
    char *value = malloc(sizeof(char*));
    value[0] = '\0';

    while(isalnum(lexer->c)) {
        char *str = lexer_get_curr_char(lexer);
        value = realloc(value, (strlen(value) + 1 + strlen(str)) * sizeof(char));
        strcat(value, str);
        free(str);
        lexer_advance(lexer);
    }

    return new_token(TOKEN_ID, value);

}

token_t *lexer_collect_string(lexer_t *lexer)
{
    lexer_advance(lexer);       // skip first "

    char *value = malloc(sizeof(char));
    value[0] = '\0';

    while(lexer->c != '"') {
        if (lexer->c == '\\' && lexer_peek(lexer) == '"')
            lexer_advance(lexer);
        char *str = lexer_get_curr_char(lexer);
        value = realloc(value, (strlen(value) + 1 + strlen(str)) * sizeof(char));
        strcat(value, str);
        free(str);
        lexer_advance(lexer);
    }
    return new_token(TOKEN_STRING, value);
}

char *lexer_get_curr_char(lexer_t *lexer)
{
    char *ret = malloc(2 * sizeof(char));
    ret[0] = lexer->c;
    ret[1] = '\0';
    return ret;
}

char lexer_peek(lexer_t *lexer)
{
    return lexer->contents[lexer->i < strlen(lexer->contents)
                            ? lexer->i + 1
                            : strlen(lexer->contents)];
}
