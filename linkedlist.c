#include "linkedlist.h"
#include "spellchecker.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Not standard function, some compilers do not have it */
static size_t _strnlen(const char *str, size_t maxlen) {
    size_t i;
    for (i = 0; i < maxlen && str[i]; i++)
        ;
    return i;
}

HeadNode *linkedlist_create(void) {
    HeadNode *head = (HeadNode *)malloc(sizeof(HeadNode));
    head->first = NULL;
    head->last_inserted = NULL;
    return head;
}

int linkedlist_free(HeadNode *head) {
    if (head == NULL) {
        return -1;
    }

    Node *current = head->first;
    Node *next = head->first->next;
    while (next != NULL) {
        if (current->word != NULL) {
            free(current->word);
        }

        if (current != NULL) {
            free(current);
        }

        current = next;
        next = next->next;
    }

    free(head);
    return 0;
}

int linkedlist_insert(HeadNode *head, char *word) {
    if (head == NULL || word == NULL) {
        return -2;
    }

    size_t word_size = _strnlen(word, (size_t)SPELLCHECKER_MAX_WORD_SIZE) + 1;
    char *new_word = (char *)malloc(word_size * sizeof(char));

    Node *new;
    new = (Node *)malloc(sizeof(Node));
    if (new == NULL) {
        return -1;
    }

    new->word = strncpy(new_word, word, word_size);

    if (head->first == NULL) {
        head->first = new;
    } else {
        head->last_inserted->next = new;
    }

    head->last_inserted = new;

    return 0;
}

int linkedlist_find(HeadNode *head, char *word) {
    Node *current = head->first;

    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return 0;
        }
        current = current->next;
    }
    return -1;
}

OptHeadNode *linkedlist_opt_create(void) {
    OptHeadNode *head = (OptHeadNode *)malloc(sizeof(OptHeadNode));

    for (int i = 0; i < LINKEDLIST_HEAD_MAX_NODES; i++) {
        head->nodes[i] = linkedlist_create();
        if (head->nodes[i] == NULL) {
            for (int j = 0; j < i; j++) {
                linkedlist_free(head->nodes[j]);
            }
            free(head);
        }
    }

    return head;
}

static unsigned int _getIndexFromWord(char *word) {
    char first = word[0];
    unsigned int index = LINKEDLIST_HEAD_MAX_NODES - 1;
    if ('a' <= first && first <= 'z') {
        /* z is index 0, a is 25, others are 26 */
        index = (unsigned int)('z' - first);
    }

    return index;
}

int linkedlist_opt_insert(OptHeadNode *head, char *word) {
    if (head == NULL && word == NULL) {
        return -1;
    }

    unsigned int index = _getIndexFromWord(word);
    HeadNode *selected = head->nodes[index];

    return linkedlist_insert(selected, word);
}

int linkedlist_opt_find(OptHeadNode *head, char *word) {
    if (head == NULL && word == NULL) {
        return -1;
    }

    unsigned int index = _getIndexFromWord(word);
    HeadNode *selected = head->nodes[index];

    return linkedlist_find(selected, word);
}

int linkedlist_opt_free(OptHeadNode *head) {
    if (head == NULL) {
        return -1;
    }

    for (int i = 0; i < LINKEDLIST_HEAD_MAX_NODES; i++) {
        if (head->nodes[i] != NULL) {
            linkedlist_free(head->nodes[i]);
        }
    }

    free(head);

    return 0;
}
