#include "linkedlist.h"
#include "spellchecker.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPELLCHECKER_INPUT_ARGUMENT_NUMBER 2

/* Set all letters of a word to lower case */
void util_toLowerCase(char *word) {
    if (word == NULL) {
        return;
    }

    for (int i = 0; word[i]; i++) {
        word[i] = (char)tolower(word[i]);
    }
}

/*
 * Check if the word is a number
 */
int util_isNumber(char *word) {
    if (word == NULL) {
        return -1;
    }

    for (int i = 0; word[i]; i++) {
        if (!isdigit(word[i])) {
            return 1;
        }
    }

    return 0;
}

/*
 * Check if the word contains any digit.
 * This will catch words like 8bits, 1526, b2b, ...
 */
int util_containsDigit(char *word) {
    if (word == NULL) {
        return -1;
    }

    for (int i = 0; word[i]; i++) {
        if (isdigit(word[i])) {
            return 1;
        }
    }

    return 0;
}

/*
 * Remove all special characters that do not constitue a word
 * ( . : , ? / ) and so on.
 */
void util_removeSpecialCharacter(char *word) {
    if (word == NULL) {
        return;
    }

    size_t length = strlen(word);

    /* You can have multiple special characters chained like: "etc,..):" */
    for (size_t i = length; i != 0; i--) {
        if (isalpha(word[i]) || isdigit(word[i])) {
            break;
        } else {
            word[i] = '\0';
        }
    }

    /* You can have multiple special characters chained like: "(#dial" */
    for (size_t i = 0; word[i]; i++) {
        if (isalpha(word[i]) || isdigit(word[i])) {
            break;
        } else {
            strcpy(word, word + 1);
        }
    }
}
