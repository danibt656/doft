#include <string.h>

#include "include/doft.h"
#include "include/macros.h"

doft *doft_get_value(doft *data, const char *key)
{
    if (!data->map) return 0;

    doft *value = (doft*)map_get_value(data->map, (char*)key);

    if (!value) {
        for (uint32_t i = 0; i < data->key_value_list_size; i++) {
            doft *v = data->key_value_list_value[i];
            if (!v) continue;
            if (!v->key_value_key) continue;
            if (strcmp(v->key_value_key, key) == 0) return v;
        }
    }

    return value;
}

char* doft_get_string(doft* data, const char* key)
{
    doft *value = doft_get_value(data, key);
    if (!value) return 0;
    return value->string_value;
}

int doft_get_int(doft* data, const char* key)
{
    doft *value = doft_get_value(data, key);
    if (!value) return 0;
    return value->int_value;
}

float doft_get_float(doft* data, const char* key)
{
    doft *value = doft_get_value(data, key);
    if (!value) return 0;
    return value->float_value;  
}

float doft_get_number(doft* data, const char* key)
{
    doft *value = doft_get_value(data, key);
    if (!value) return 0;
    return OR(value->float_value, value->int_value);
}


doft_iterator iterate(doft *data)
{
    if (!doft_is_list(data)) return (doft_iterator){0, 0, 0};
    doft_iterator iterator = {};
    iterator.values = data->list_value;
    iterator.length = data->list_size;
    iterator.index = 0;
    iterator.current = iterator.values[iterator.index];
    return iterator;
}

doft *doft_iterator_next(doft_iterator *iterator)
{
    doft *current = iterator->current;
    if (iterator->index < iterator->length) {
        iterator->index++;
        iterator->current = iterator->values[iterator->index];
    } else {
        iterator->current = 0;
    }

    return current;
}

unsigned int doft_is_list(doft *data)
{
    return data->type == AST_LIST;
}

char *doft_string(doft *data)
{
    if (!data) return 0;
    return OR(data->string_value, data->key_value_key);
}

int doft_int(doft *data)
{
    if (!data) return 0;
    return data->int_value;
}

float doft_float(doft *data)
{
    if (!data) return 0;
    return data->int_value;
}

float doft_number(doft *data)
{
    if (!data) return 0;
    return OR(data->float_value, data->int_value);
}
