#ifndef DOFT_H
#define DOFT_H

#include "doft_lexer.h"
#include "doft_parser.h"
#include "doft_visitor.h"

typedef ast_t doft;

typedef struct DOFT_ITERATOR_STRUCT {
    doft **values;
    doft *current;
    uint32_t index;
    uint32_t length;
} doft_iterator;

doft *doft_get_value(doft *data, const char *key);
char* doft_get_string(doft* data, const char* key);
int doft_get_int(doft* data, const char* key);
float doft_get_float(doft* data, const char* key);
float doft_get_number(doft* data, const char* key);


doft_iterator iterate(doft *data);

doft *doft_iterator_next(doft_iterator *iterator);

unsigned int doft_is_list(doft *data);

char *doft_string(doft *data);
int doft_int(doft *data);
float doft_float(doft *data);
float doft_number(doft *data);

#endif