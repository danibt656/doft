#ifndef DOFT_PARSER_H
#define DOFT_PARSER_H
#include <stdio.h>
#include <stdlib.h>

#include "doft_ast.h"
#include "doft_lexer.h"

typedef struct PARSER_STRUCT {
    lexer_t *lexer;
    token_t *curr_token;
    token_t **stack;

    size_t stack_size;
} parser_t;

parser_t *new_parser(lexer_t *lexer);

void parser_free(parser_t *parser);

void parser_eat(parser_t *parser, int type);

void parser_stack(parser_t *parser, token_t *token);

ast_t *parser_parse(parser_t *parser);

ast_t *parser_parse_key_value_list(parser_t *parser);

ast_t *parser_parse_key_value(parser_t *parser);

ast_t *parser_parse_string(parser_t *parser);

ast_t *parser_parse_id(parser_t *parser);

ast_t *parser_parse_int(parser_t *parser);

ast_t *parser_parse_float(parser_t *parser);

ast_t *parser_parse_list(parser_t *parser);

#endif