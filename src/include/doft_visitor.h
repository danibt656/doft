#ifndef DOFT_VISITOR_H
#define DOFT_VISITOR_H
#include "doft_ast.h"

ast_t *visitor_visit(ast_t *ast);

ast_t *visitor_visit_id(ast_t *ast);

ast_t *visitor_visit_int(ast_t *ast);

ast_t *visitor_visit_float(ast_t *ast);

ast_t *visitor_visit_string(ast_t *ast);

ast_t *visitor_visit_list(ast_t *ast);

ast_t *visitor_visit_key_value(ast_t *ast);

ast_t *visitor_visit_key_value_list(ast_t *ast);

#endif