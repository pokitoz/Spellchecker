#include "linkedlist.h"
#include "spellchecker.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#ifndef MAIN_USE_LINKEDLIST_OPTIMIZE
/* Use an optimized linked list */
#define MAIN_USE_LINKEDLIST_OPTIMIZE 1
#endif

/*
 * This program takes 2 arguments:
 *  - The first is the dictionary
 *  - The second is the text file to be checked
 */
#define MAIN_INPUT_ARGUMENT_NUMBER 2

int main(int argc, char *argv[]) {
    /* Check arguments */
    if (argc <= MAIN_INPUT_ARGUMENT_NUMBER) {
        printf("Usage: ./spellcheck dictionary.txt text.txt\n");
        return EINVAL;
    }

    clock_t begin = clock();

    /* When opening the file, the path length will be checked */
    char *dictionary_path = argv[1];
    char *text_path = argv[2];

    /* Open files */
    FILE *dictionary;
    int errnum;
    dictionary = fopen(dictionary_path, "r");
    if (dictionary == NULL) {
        errnum = errno;
        printf("main: Error opening file %s: %s\n", dictionary_path,
               strerror(errnum));
        return errnum;
    }

    /* Create linkedlist */
#if MAIN_USE_LINKEDLIST_OPTIMIZE == 0
    HeadNode *head = linkedlist_create();
#else
    OptHeadNode *head = linkedlist_opt_create();
#endif

    char word[SPELLCHECKER_WORD_ARRAY_SIZE];
    while (fscanf(dictionary, SPELLCHECKER_INPUT_STRING_FORMAT, word) != EOF) {
        util_toLowerCase(word);

#if MAIN_USE_LINKEDLIST_OPTIMIZE == 0
        /* Fill linkedlist */
        if (linkedlist_insert(head, word) != 0) {
#else
        /* Fill linkedlist */
        if (linkedlist_opt_insert(head, word) != 0) {
#endif
            printf("main: Could not insert '%s'\n", word);
            return -5;
        }
    }

    /* No need to keep the dictionary open*/
    fclose(dictionary);

    /* Open the text that needs to be tested */
    FILE *text;
    text = fopen(text_path, "r");
    if (text == NULL) {
        errnum = errno;
        printf("main: Error opening file %s: %s\n", text_path, strerror(errnum));
        return errnum;
    }

    /* Until the end of the file, process all words. */
    while (fscanf(text, SPELLCHECKER_INPUT_STRING_FORMAT, word) != EOF) {
        util_removeSpecialCharacter(word);
        util_toLowerCase(word);
        if (util_containsDigit(word) || word[0] == '\0') {
            /* Skip numbers and other word containing numbers
             * and null characters
             */
            continue;
        }

#if MAIN_USE_LINKEDLIST_OPTIMIZE == 0
        if (linkedlist_find(head, word) != 0) {
#else
        if (linkedlist_opt_find(head, word) != 0) {
#endif

            /* Check each word by finding it into the linkedlist
             * If the word is not in the dictionary; print it.
             */

            long int position = ftell(text);
            printf("'%s' at %ld\n", word, position);
        }
    }

    fclose(text);

#if MAIN_USE_LINKEDLIST_OPTIMIZE == 0
    /* Free all elements in the linkedlist */
    linkedlist_free(head);
#else
    linkedlist_opt_free(head);
#endif

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("main: Done in %lf sec\n", time_spent);
    return EXIT_SUCCESS;
}
