#include <stdio.h>
#include <string.h>

#include "include/json_ast.h"
#include "include/json_parser.h"

#define CURR_TOKEN() parser->curr_token

parser_t *new_parser(lexer_t *lexer)
{
    parser_t *new_parser = malloc(sizeof(struct PARSER_STRUCT));
    new_parser->lexer = lexer;
    new_parser->curr_token = lexer_get_next_token(lexer);
    new_parser->stack = (void *)0;
    new_parser->stack_size = 0;

    return new_parser;
}

void parser_free(parser_t *parser)
{
    if (parser->lexer)
        lexer_free(parser->lexer);
    if (parser->stack != (void*)0) {
        for (int i = 0; i < parser->stack_size; i++)
            token_free(parser->stack[i]);
        free(parser->stack);
    }
    free(parser);
}

void parser_eat(parser_t *parser, int type)
{
    parser_stack(parser, parser->curr_token);

    if (parser->curr_token->type != type) {
        printf("[json_parser] Unexpected token of type (%d, %s)\n",
                parser->curr_token->type, parser->curr_token->value);
        printf("Was expecting %d.\n(lexer->i == %d)\n", type, parser->lexer->i);
        exit(1);
    }
    parser->curr_token = lexer_get_next_token(parser->lexer);
}

void parser_stack(parser_t *parser, token_t *token)
{
    parser->stack_size += 1;

    if (parser->stack == (void *)0)
        parser->stack = malloc(sizeof(struct JSON_JSON_AST_STRUCT *));
    else
        parser->stack = realloc(parser->stack, parser->stack_size *
                                               sizeof(struct JSON_JSON_AST_STRUCT *));

    parser->stack[parser->stack_size - 1] = token;
}

ast_t *parser_parse(parser_t *parser)
{
    if (CURR_TOKEN() != (void*)0) {
        switch (CURR_TOKEN()->type) {
            case TOKEN_STRING : return parser_parse_string(parser); break;
            case TOKEN_INT : return parser_parse_int(parser); break;
            case TOKEN_FLOAT : return parser_parse_float(parser); break;
            case TOKEN_LBRACE : return parser_parse_key_value_list(parser); break;
            case TOKEN_LBRACKET : return parser_parse_list(parser); break;
            case TOKEN_ID : return parser_parse_id(parser); break;
            case TOKEN_COMMA : break;
            case TOKEN_RBRACE : break;
            case TOKEN_RBRACKET : break;
            case TOKEN_COLON : printf("curr_token: %d\n", CURR_TOKEN()->type); break;
            default : break;
        }

        printf("[json_parser] Unexpected TOKEN(%d, %s)\n", CURR_TOKEN()->type, CURR_TOKEN()->value);
        
        return (void*)0;
    }
}

ast_t *parser_parse_key_value_list(parser_t *parser)
{
    ast_t *ast = new_ast(AST_KEY_VALUE_LIST);
    ast->key_value_list_value = (void *)0;

    parser_eat(parser, TOKEN_LBRACE);
    
    if (CURR_TOKEN()->type != TOKEN_RBRACE) {
        ast->key_value_list_size += 1;
        ast->key_value_list_value = realloc(ast->key_value_list_value,
                                ast->key_value_list_size * sizeof(struct AST_STRUCT));

        ast_t* kv = parser_parse_key_value(parser);
        ast->key_value_list_value[ast->key_value_list_size - 1] = kv;

        map_set(ast->map, kv->key_value_key, kv->key_value_value);

        if (CURR_TOKEN()->type == TOKEN_COMMA)
            parser_eat(parser, TOKEN_COMMA);
        
        while (CURR_TOKEN()->type == TOKEN_STRING || CURR_TOKEN()->type == TOKEN_INT || CURR_TOKEN()->type == TOKEN_FLOAT) {
            ast->key_value_list_size += 1;
            ast->key_value_list_value = realloc(ast->key_value_list_value, ast->key_value_list_size * sizeof(struct AST_STRUCT));
            
            ast_t* kv =  parser_parse_key_value(parser);
            
            ast->key_value_list_value[ast->key_value_list_size - 1] = kv;
            
            map_set(ast->map, kv->key_value_key, kv->key_value_value);
            
            if (CURR_TOKEN()->type == TOKEN_COMMA)
                parser_eat(parser, TOKEN_COMMA);

            if (CURR_TOKEN()->type == TOKEN_RBRACE)
                break;
        }
    }

    parser_eat(parser, TOKEN_RBRACE);

    return ast;
}

ast_t *parser_parse_key_value(parser_t *parser)
{
    ast_t *ast = new_ast(AST_KEY_VALUE);

    ast->key_value_key = malloc((strlen(CURR_TOKEN()->value) + 1) * sizeof(char));
    strcpy(ast->key_value_key, CURR_TOKEN()->value);

    parser_eat(parser, TOKEN_STRING);
    parser_eat(parser, TOKEN_COLON);

    ast->key_value_value = parser_parse(parser);

    return ast;
}

ast_t *parser_parse_string(parser_t *parser)
{
    ast_t *ast = new_ast(AST_STRING);
    ast->string_value = malloc(strlen((CURR_TOKEN()->value) + 1) * sizeof(char));
    strcpy(ast->string_value, CURR_TOKEN()->value);
    parser_eat(parser, TOKEN_STRING);
    return ast;
}

ast_t *parser_parse_id(parser_t *parser)
{
    ast_t *ast = new_ast(AST_ID);
    ast->string_value = malloc(strlen((CURR_TOKEN()->value) + 1) * sizeof(char));
    strcpy(ast->string_value, CURR_TOKEN()->value);
    parser_eat(parser, TOKEN_ID);

    return ast;
}

ast_t *parser_parse_int(parser_t *parser)
{
    ast_t *ast = new_ast(AST_INT);
    ast->int_value = atoi(CURR_TOKEN()->value);
    parser_eat(parser, TOKEN_INT);

    return ast;
}

ast_t *parser_parse_float(parser_t *parser)
{
    ast_t *ast = new_ast(AST_FLOAT);
    ast->float_value = atof(CURR_TOKEN()->value);
    parser_eat(parser, TOKEN_FLOAT);

    return ast;
}

ast_t *parser_parse_list(parser_t *parser)
{
    ast_t *ast = new_ast(AST_LIST);
    ast->list_value = (void*)0;

    parser_eat(parser, TOKEN_LBRACKET);

    if (CURR_TOKEN()->type == TOKEN_RBRACKET) {
        parser_eat(parser, TOKEN_RBRACKET);
        return ast;
    }

    ast->list_size += 1;
    ast->list_value = realloc(ast->list_value, ast->list_size * sizeof(struct AST_STRUCT));
    ast->list_value[ast->list_size - 1] = parser_parse(parser);

    while (CURR_TOKEN()->type == TOKEN_COMMA) {
        parser_eat(parser, TOKEN_COMMA);

        ast->list_size += 1;
        ast->list_value = realloc(ast->list_value, ast->list_size * sizeof(struct AST_STRUCT));
        ast->list_value[ast->list_size - 1] = parser_parse(parser);
    }

    parser_eat(parser, TOKEN_RBRACKET);

    return ast;
}
