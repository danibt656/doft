#ifndef JSON_H
#define JSON_H

#include "json_lexer.h"
#include "json_parser.h"
#include "json_visitor.h"

typedef ast_t json;

typedef struct JSON_ITERATOR_STRUCT {
    json **values;
    json *current;
    uint32_t index;
    uint32_t length;
} json_iterator;

json *json_get_value(json *data, const char *key);
char* json_get_string(json* data, const char* key);
int json_get_int(json* data, const char* key);
float json_get_float(json* data, const char* key);
float json_get_number(json* data, const char* key);


json_iterator iterate(json *data);

json *json_iterator_next(json_iterator *iterator);

unsigned int json_is_list(json *data);

char *json_string(json *data);
int json_int(json *data);
float json_float(json *data);
float json_number(json *data);

#endif