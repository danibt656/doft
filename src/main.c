#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "include/doft.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Must specify file to parse.\n");
        exit(1);
    }

    parser_t *parser = new_parser(new_lexer(lexer_read_file(argv[1])));
    
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
