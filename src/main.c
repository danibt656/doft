#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "include/doft.h"

char *read_file(const char *filename) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Could not open %s\n", filename);
        exit(1);
    }

    char *data = calloc(1, sizeof(char));
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        data = realloc(data, (strlen(data) + strlen(line) + 1) * sizeof(char));
        strcat(data, line);
    }

    fclose(fp);

    if (line)
        free(line);

    return data;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Must specify file to parse.\n");
        exit(1);
    }

    parser_t *parser = new_parser(new_lexer(read_file(argv[1])));
    
    ast_t *ast = parser_parse(parser);
    
    doft_iterator iterator = iterate(ast);
    
    while (iterator.current) {
        char* str = doft_string(iterator.current);
        printf(":> %s\n", str);
        doft_iterator_next(&iterator);
    }
    
    printf("\n");
    visitor_visit(ast);
    printf("\n\n");
    
    parser_free(parser);
    printf("Freed ast\n");
    ast_free(ast);
}
