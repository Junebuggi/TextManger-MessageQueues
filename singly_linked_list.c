/**
 * This program contains functions to create and manipulate
 * singly linked lists.
 *
 * @author Emma Boulay
 */

#include "singly_linked_list.h"

/**
 * This function will create a new strnode that points to next
 *
 * @param sentence the sentence value of the new node
 * @param next the strnode the new node will point to
 * @return the new node
 */
strnode_t *strnode_construct(char* sentence, strnode_t *next)
{
    strnode_t *new = malloc(sizeof(strnode_t));
    assert (new != NULL);
    new->sentence = malloc(sizeof(char)*strlen(sentence)); //allocate space for sentence
    strcpy(new->sentence, sentence);
    new->next = next;
    return new; //return new node
}

/**
 * This function will iterate over the linked list and print
 * node's sentence.
 * @param head The head of the linked list to be printed
 */
void print_list(strnode_t *head)
{
    if (head == NULL) {
        printf("Text-Manager is empty");
    } else{
        for (strnode_t *curr = head; curr != NULL; curr = curr->next) {
            printf("%s ", curr->sentence);
        }
        printf("\n");
    }
}

/**
 * This function will free all the memory allocated by malloc
 * for the node
 * @param node The node to be deleted
 */
void deleteNode(strnode_t* node){
    if(node->sentence != NULL){
        free(node->sentence); //Free all memory for the sentence
    }
    if(node != NULL){
        free(node); //Free all memory for the node
    }
}
