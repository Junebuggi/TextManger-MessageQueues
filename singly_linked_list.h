/**
 * This is the header file for the singly linked list functions
 */
#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Represents a node in a singly-linked-list that
 * stores a pointer to a sentence. Used to store
 * all of the user sentences in Text-Manager
 */
typedef struct strnode {
    char*    sentence;
    struct strnode *next;
} strnode_t;

/* Function declarations */
strnode_t *strnode_construct(char* sentence, strnode_t *next);
void print_list(strnode_t *head);
void deleteNode(strnode_t* node);

#endif