#ifndef JSON_AST_H
#define JSON_AST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hashmap.h"

typedef struct AST_STRUCT {
    enum {
        AST_KEY_VALUE,
        AST_KEY_VALUE_LIST,
        AST_STRING,
        AST_INT,
        AST_FLOAT,
        AST_LIST,
        AST_ID
    } type;

    char *string_value;
    int int_value;
    float float_value;

    struct AST_STRUCT **list_value;
    uint32_t list_size;

    char *key_value_key;
    struct AST_STRUCT *key_value_value;

    struct AST_STRUCT **key_value_list_value;
    size_t key_value_list_size;
    
    map_T *map;
} ast_t;

ast_t *new_ast(int type);

void ast_free(ast_t *ast);

#endif