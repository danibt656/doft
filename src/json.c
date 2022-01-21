#include <string.h>

#include "include/json.h"
#include "include/macros.h"

json *json_get_value(json *data, const char *key)
{
    if (!data->map) return 0;

    json *value = (json*)map_get_value(data->map, (char*)key);

    if (!value) {
        for (uint32_t i = 0; i < data->key_value_list_size; i++) {
            json *v = data->key_value_list_value[i];
            if (!v) continue;
            if (!v->key_value_key) continue;
            if (strcmp(v->key_value_key, key) == 0) return v;
        }
    }

    return value;
}

char* json_get_string(json* data, const char* key)
{
    json *value = json_get_value(data, key);
    if (!value) return 0;
    return value->string_value;
}

int json_get_int(json* data, const char* key)
{
    json *value = json_get_value(data, key);
    if (!value) return 0;
    return value->int_value;
}

float json_get_float(json* data, const char* key)
{
    json *value = json_get_value(data, key);
    if (!value) return 0;
    return value->float_value;  
}

float json_get_number(json* data, const char* key)
{
    json *value = json_get_value(data, key);
    if (!value) return 0;
    return OR(value->float_value, value->int_value);
}


json_iterator iterate(json *data)
{
    if (!json_is_list(data)) return (json_iterator){0, 0, 0};
    json_iterator iterator = {};
    iterator.values = data->list_value;
    iterator.length = data->list_size;
    iterator.index = 0;
    iterator.current = iterator.values[iterator.index];
    return iterator;
}

json *json_iterator_next(json_iterator *iterator)
{
    json *current = iterator->current;
    if (iterator->index < iterator->length) {
        iterator->index++;
        iterator->current = iterator->values[iterator->index];
    } else {
        iterator->current = 0;
    }

    return current;
}

unsigned int json_is_list(json *data)
{
    return data->type == AST_LIST;
}

char *json_string(json *data)
{
    if (!data) return 0;
    return OR(data->string_value, data->key_value_key);
}

int json_int(json *data)
{
    if (!data) return 0;
    return data->int_value;
}

float json_float(json *data)
{
    if (!data) return 0;
    return data->int_value;
}

float json_number(json *data)
{
    if (!data) return 0;
    return OR(data->float_value, data->int_value);
}