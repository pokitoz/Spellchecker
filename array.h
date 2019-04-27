#ifndef ARRAY_H__
#define ARRAY_H__

typedef struct array_head {
    char** array;
    unsigned int size;
    unsigned int filled; /* Number of word in the array */
} array_head;

array_head array_create(int size);
int array_add(array_head head, char* word);
int array_find(array_head head, char* word);
int array_free(array_head head);

#endif
