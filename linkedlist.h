#ifndef LINKEDLIST_H__
#define LINKEDLIST_H__

#define LINKEDLIST_HEAD_MAX_NODES 27

typedef struct Node Node;

struct Node {
    char* word;
    Node* next;
};

typedef struct HeadNode {
    Node* first;
    Node* last_inserted;
} HeadNode;

typedef struct OptHeadNode {
    HeadNode* nodes[LINKEDLIST_HEAD_MAX_NODES];
    HeadNode* last[LINKEDLIST_HEAD_MAX_NODES];
} OptHeadNode;


OptHeadNode* linkedlist_opt_create(void);
int linkedlist_opt_insert(OptHeadNode* head, char* word);
int linkedlist_opt_find(OptHeadNode* head, char* word);
int linkedlist_opt_free(OptHeadNode* head);

HeadNode* linkedlist_create(void);
int linkedlist_insert(HeadNode* head, char* word);
int linkedlist_find(HeadNode* head, char* word);
int linkedlist_free(HeadNode* head);

#endif
