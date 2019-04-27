#include "array.h"
#include "spellchecker.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

array_head array_create(unsigned int size) {
    array_head* head = (array_head*) malloc(sizeof(array_head);
    if(head ==NULL) {
    return NULL;
}
char** array = (char**) calloc(size, sizeof(char*));
if(array == NULL) {
    free(head);
        return NULL;
    }
    head->size = size;
                 head->array = array;
                 head->filled = 0;
                 return head;
}
int array_add(array_head head, char *word) {
    char **array = head->array;
    unsigned int size = head->size;
    array[head->filled] = (char*) malloc(length*sizeof(char);
                                         head->filled = head->filled + 1;
                                         return 0;
}
int array_free(array_head head) {}
