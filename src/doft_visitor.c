#include <stdio.h>
#include "include/doft_visitor.h"


ast_t *visitor_visit(ast_t *ast)
{
    switch (ast->type) {
        case AST_KEY_VALUE: return visitor_visit_key_value(ast); break;
        case AST_KEY_VALUE_LIST: return visitor_visit_key_value_list(ast); break;
        case AST_LIST: return visitor_visit_list(ast); break;
        case AST_ID: return visitor_visit_id(ast); break;
        case AST_INT: return visitor_visit_int(ast); break;
        case AST_FLOAT: return visitor_visit_float(ast); break;
        case AST_STRING: return visitor_visit_string(ast); break;
    }

    printf("[doft_visitor] Unhandled doft_ast->type %d\n", ast->type);
    exit(1);

    return ast;
}

ast_t *visitor_visit_id(ast_t *ast)
{
    printf("%s", ast->string_value);
    return ast;
}

ast_t *visitor_visit_int(ast_t *ast)
{
    printf("%d", ast->int_value);
    return ast;
}

ast_t *visitor_visit_float(ast_t *ast)
{
    printf("%.2f", ast->float_value);
    return ast;
}

ast_t *visitor_visit_string(ast_t *ast)
{
    printf("%s", ast->string_value);
    return ast;
}

ast_t *visitor_visit_list(ast_t *ast)
{
    printf("[");

    for (int i = 0; i < ast->list_size; i++) {
        visitor_visit(ast->list_value[i]);

        if (i < ast->list_size - 1)
            printf(",");
    }
    printf ("]");
    return ast;
}

ast_t *visitor_visit_key_value(ast_t *ast)
{
    printf("\"%s\": ", ast->key_value_key);
    visitor_visit(ast->key_value_value);
    return ast;
}

ast_t *visitor_visit_key_value_list(ast_t *ast)
{
    printf("{");

    for (int i = 0; i < ast->key_value_list_size; i++) {
        visitor_visit(ast->key_value_list_value[i]);

        if (i < ast->key_value_list_size - 1)
            printf(",");
    }

    printf("}");
    return ast;
}