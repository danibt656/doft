#include "include/json_ast.h"


ast_t *new_ast(int type)
{
    ast_t *new_ast = malloc(sizeof(struct AST_STRUCT));
    new_ast->type = type;
    new_ast->string_value = (void *)0;
    new_ast->list_value = (void *)0;
    new_ast->list_size = 0;
    new_ast->key_value_list_value = (void *)0;
    new_ast->key_value_list_size = 0;

    if (type == AST_KEY_VALUE_LIST)
        new_ast->map = NEW_MAP();

    return new_ast;
}

void ast_free(ast_t *ast)
{
    switch (ast->type) {
        case AST_STRING : free(ast->string_value); break;
        case AST_FLOAT : break;
        case AST_INT : break;
        case AST_LIST : {
            for (int i=0; i < ast->list_size; i++) {
                ast_free(ast->list_value[i]);
            }
            free(ast->list_value);
        } break;
        case AST_KEY_VALUE_LIST : {
            map_free(ast->map);
            for (int i=0; i < ast->key_value_list_size; i++) {
                ast_t *kv = ast->key_value_list_value[i];
                ast_free(kv);
            }
            free(ast->key_value_list_value);
        } break;
        case AST_KEY_VALUE : {
            if (ast->key_value_key)
                free(ast->key_value_key);
            if (ast->key_value_value)
                ast_free(ast->key_value_value);
        }
        default: break;
    }

    free(ast);
}