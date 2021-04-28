/**
 * The Text-Manager will wait to receive commands from the user in the message queue. And
 * will then read in the parameters from the message queue and will then execute the command.
 * The Text-Manager keeps track of the current dialogue and provides functions to manipulate
 * the stored text. The dialogue is stored as a singly linked list, where each sentence is
 * a new node.
 *
 * @author Emma Boulay
 */

#include "shared.h"
#include "singly_linked_list.h"

/* Function Declarations for Text-Manager command operation */
void updateAverage(struct Average_t* avg, struct timeval start, struct timeval end);
strnode_t* append(strnode_t* storedText, char* newSentence);
void delete(strnode_t* storedText, char* toRemove);
strnode_t*  removeTarget(strnode_t* storedText, char* toRemove);
char* search(strnode_t* storedText, char* targetWord);
char* getNextSentence(char** sentences);
int isLetter(char a);
int isEndPunctuation(char a);

/**
 * The main function of the Text-Manager
 */
int main() {
    /* Instantiate and create the textManager and user message queues */
    int toTextManagerQueue = createMsgQueue(TEXT_MANAGER_KEY);
    int toUserQueue = createMsgQueue(USER_KEY);
    Message message;
    strnode_t *storedText = NULL;

    /* Used to instrument each command */
    struct timeval start, end;

    /* Used to keep track of the average execution time for each command */
    struct Average_t *avg[4];

    /* Initialize each Average_t struct pointer */
    for(int i = 0; i < 4; i++){
        avg[i] = (struct Average_t *) malloc(sizeof(struct Average_t));
        avg[i]->average = 0;
        avg[i]->n = 0;
    }

    int running = 1;
    while (running){
        char* procedure = receiveMsg(toTextManagerQueue);
        printf("Command received: %s\n", procedure);
        /* Check if the command is append */
        if(strncasecmp(procedure, "append",  6) == 0){
            /* Get the sentence to append */
            char* appendStr = receiveMsg(toTextManagerQueue);
            /* Instrument the append function */
            gettimeofday(&start, NULL);
            storedText = append(storedText, appendStr);
            gettimeofday(&end, NULL);

            /* Update the average execution time */
            updateAverage(avg[0], start, end);

            printf("Message from user appended\n");
            printf("String stored in Text-Manager is now:\n");
            print_list(storedText);
            printf("\n");
        }
        /* Check if the command is delete */
        else if(strncasecmp(procedure, "delete",  6) == 0){
            /* Get word to delete */
            char* deleteStr = receiveMsg(toTextManagerQueue);
            /* Instrument the delete function */
            gettimeofday(&start, NULL);
            delete(storedText, deleteStr);
            gettimeofday(&end, NULL);

            /* Update the average execution time */
            updateAverage(avg[1], start, end);

            printf("All occurrences of user-word <%s> deleted\n", deleteStr);
            printf("String stored in Text-Manager is now:\n");
            print_list(storedText);
            printf("\n");
        }
        /* Check if the command is remove */
        else if(strncasecmp(procedure, "remove",  6) == 0){
            /* Get the word in the sentence to remove */
            char* removeStr = receiveMsg(toTextManagerQueue);
            /* Instrument the remove function */
            gettimeofday(&start, NULL);
            storedText = removeTarget(storedText, removeStr);
            gettimeofday(&end, NULL);

            /* Update the average execution time */
            updateAverage(avg[2], start, end);

            printf("First sentence including user-word <%s> removed\n", removeStr);
            printf("String stored in Text-Manager is now:\n");
            print_list(storedText);
            printf("\n");
        }
        /* Check if the command is search */
        else if(strncasecmp(procedure, "search",  6) == 0){
            /* Get the word in the sentence to find */
            char* searchStr = receiveMsg(toTextManagerQueue);
            /* Instrument the search function */
            gettimeofday(&start, NULL);
             char* sentence = search(storedText, searchStr);
             gettimeofday(&end, NULL);

             /* Update the average execution time */
             updateAverage(avg[3], start, end);

             /* Send the string found to the user */
             strcpy(message.sentence, sentence);
             sendMsg(toUserQueue, message);

            if(strcmp(message.sentence, "Does not contain string!") == 0)
                printf("User string could not be found\n");
            else
                printf("Sentence found and sent to user\n");
        }
        /* If the command is exit, print the average execution times for each command */
        else if(strncasecmp(procedure, "exit",  4) == 0){
            running = 0;
            printf("Average time for append operation: %.2f ms. Total of %d samples\n", avg[0]->average, avg[0]->n);
            printf("Average time for delete operation: %.2f ms. Total of %d samples\n", avg[1]->average, avg[1]->n);
            printf("Average time for remove operation: %.2f ms. Total of %d samples\n", avg[2]->average, avg[2]->n);
            printf("Average time for search operation: %.2f ms. Total of %d samples\n", avg[3]->average, avg[3]->n);
        }
    }
    /* Delete the toUser and toTextManager message queues */
    deleteMsgQueue(toUserQueue);
    deleteMsgQueue(toTextManagerQueue);
}

/**
 * This function is used to append a new sentence to the existing text stored
 * in the Text-Manager. It creates a new strnode and traverses the linked list
 * to append to the end. It will also check if the user tried to append more than
 * 1 sentence, and will seperate each into their own node.
 *
 * @param storedText the singly linked list of all the sentences stored in text-manager
 * @param newSentence the new sentence to be appended
 */
strnode_t* append(strnode_t* storedText, char* newSentence){
    /* If user didn't have string at the end of the sentence, add one */
    if(!(isEndPunctuation(newSentence[(int) strlen(newSentence) -1])))
        newSentence = strcat(newSentence, ".");

    /* If this is the first node */
    if (storedText == NULL) {
        storedText = strnode_construct(getNextSentence(&newSentence), NULL);
    }

    strnode_t *curr;
    /* Traverse the linked list */
    for (curr = storedText; curr->next != NULL; curr = curr->next) {}
    /* If the user tried to append more than 1 sentence at once, append it */
    while(newSentence != NULL) {
        curr->next = strnode_construct(getNextSentence(&newSentence), NULL);
        curr = curr->next;
    }
    /* return the pointer to head */
    return storedText;
}

/**
 * This function will delete every occurrence of the specified word from
 * the message store in Text-Manager. It will iterate over each sentence in
 * each node of the linked list.
 *
 * @param storedText the singly linked list of all the sentences stored in text-manager
 * @param toRemove The word to be removed
 */
void delete(strnode_t* storedText, char* toRemove) {
    int i, j, messageLen, toRemoveLen, found;

    /* Get the length for both strings */
    toRemoveLen = (int) strlen(toRemove);
    /* Iterate over each sentence in the list */
    for (strnode_t *curr = storedText; curr != NULL; curr = curr->next) {
        messageLen = (int) strlen(curr->sentence);
        /* Iterate over the sentence */
        for (i = 0; i <= messageLen - toRemoveLen; i++) {
            found = 1;

            /* At every index try to match the remove word to the sentence */
            for (j = 0; j < toRemoveLen; j++) {
                if (curr->sentence[i + j] != toRemove[j]) {
                    found = 0;
                    break;
                }
            }
            /* This will make sure that it's not a partial match. ie the target word is apple but it matched to applesauce */
            if (found == 1 && (i == 0 && isLetter(curr->sentence[toRemoveLen])) ||
                found == 1 && (isLetter(curr->sentence[i - 1]) && isLetter(curr->sentence[i + toRemoveLen])) ||
                found == 1 && (isLetter(curr->sentence[i - 1]) && isLetter(curr->sentence[messageLen - 1]))) {
                found = 0;
            }

            /* If a match is found, remove the word */
            if (found == 1) {
                /* Shift all the characters to the left */
                for (j = i; j <= messageLen - toRemoveLen; j++) {
                    curr->sentence[j] = curr->sentence[j + toRemoveLen];
                }
                messageLen = messageLen - toRemoveLen;
                i--; //Attempt to match the next occurrence of the word from this index
            }
        }
    }
}

/**
 * This function will remove the first sentence that contains the
 * specified word. It will remove the node from the linked list and
 * then free all the allocated memory in the removed node.
 *
 * @param storedText the singly linked list of all the sentences stored in text-manager
 * @param toRemove The word in the sentence to be removed
 */
strnode_t* removeTarget(strnode_t* storedText, char* toRemove){
    int i, j;
    int len, toRemoveLen;
    int found;

    /* Get the length of the string to be removed */
    toRemoveLen = (int) strlen(toRemove);
    /* Iterate over the message string to find match, keep track of the previous node */
    strnode_t *curr = storedText;
    strnode_t *prev = curr;
    for (; curr != NULL; curr = curr->next) {
        len = (int) strlen(curr->sentence);
        /* Iterate over the node's sentence */
        for(i=0; i<len; i++) {
            found = 1;
            /* At every index try to match the target word to the sentence */
            for(j=0; j<toRemoveLen; j++) {
                if(curr->sentence[i+j] != toRemove[j]){
                    found = 0;
                    break;
                }
            }
            /* This will make sure that it's not a partial match. ie the target word is apple but it matched to applesauce */
            if (found == 1 && (i == 0 && isLetter(curr->sentence[toRemoveLen])) ||
                found == 1 && (isLetter(curr->sentence[i - 1]) && isLetter(curr->sentence[i + toRemoveLen])) ||
                found == 1 && (isLetter(curr->sentence[i - 1]) && isLetter(curr->sentence[len - 1]))) {
                found = 0;
            }
            if(found == 1){
                /* If the node to be removed is the only one in the list, list is now NULL */
                if(storedText->next == NULL){
                    storedText = NULL;
                }
                /* If the node to be removed is the first in the list, change the head pointer*/
                else if(prev == curr){
                    storedText = storedText->next;
                }
                /* If the node to be removed is in the middle, point prev.next to skip the current node*/
                else{
                    prev->next = curr->next;
                }
                /* Free memory allocated to the removed node */
                deleteNode(curr);
                return storedText;
            }
        }
        prev = curr;
    }
    return storedText;
}

/**
 * This function searches for and returns the first sentence that contains
 * the specified word. It will return the sentence value of the target node.
 *
 * @param storedText the singly linked list of all the sentences stored in text-manager
 * @param word The word in the target sentence
 * @return The first sentence that contains targetWord
 */
char* search(strnode_t* storedText, char* targetWord){
    int i, j, len, targetLen, found;

    /* Get the length for the target word */
    targetLen = (int) strlen(targetWord);
    char* targetSentence = "Does not contain string!";
    /* Iterate over the sentences list to find match */
    for (strnode_t *curr = storedText; curr != NULL; curr = curr->next) {
        len = (int) strlen(curr->sentence);
        /* Iterate over the sentence stored in the node */
        for(i=0; i<len; i++){
            found = 1;
            /* At every index try to match the target word to the sentence */
            for(j=0; j<targetLen; j++){
                if(curr->sentence[i+j] != targetWord[j]){
                    found = 0;
                    break;
                }
            }
            /* This will make sure that it's not a partial match. ie the target word is apple but it matched to applesauce */
            if (found == 1 && (i == 0 && isLetter(curr->sentence[targetLen])) ||
                    found == 1 && (isLetter(curr->sentence[i - 1]) && isLetter(curr->sentence[i + targetLen])) ||
                    found == 1 && (isLetter(curr->sentence[i - 1]) && isLetter(curr->sentence[len - 1]))) {
                found = 0;
            }
            /* Target word found! */
            if(found == 1){
               targetSentence = curr->sentence;
               break;
            }
        }
    }
    return targetSentence;
}

/**
 * This function is used to update the average variable when a new execution
 * time is to be added
 *
 * @param avg The Average_t struct for this command
 * @param start The start time of the execution
 * @param end The end time of the execution
 */
void updateAverage(struct Average_t* avg, struct timeval start, struct timeval end){
    long int time = (end.tv_sec * MICRO_SEC_IN_SEC + end.tv_usec) - (start.tv_sec * MICRO_SEC_IN_SEC + start.tv_usec);
    avg->average = ((avg->average * (float) avg->n) + (float) time)/((float) avg->n+1);
    ++avg->n;
}

/**
 * This function is used to separate the sentences (by period) passed to the
 * text-manager. This is to ensure that if the user tries to append multiple
 * sentences at once, each sentence is stored in its own node. If the there
 * are multiple sentences, the ptr to "sentences" now starts at the next sentence
 *
 * @param sentences The sentences to be appended.
 * @return char ptr to of the next sentence
 */
char* getNextSentence(char** sentences){
    /* Find the index of the first period*/
    int index;
    for(index = 0; !isEndPunctuation((*(sentences))[index]); index++){ }
    /* allocate space to store the next sentence */
    char* str = malloc(sizeof(char) * (index+1));
    int i;
    /* Copy the sentence to the array to be returned */
    for(i = 0; i == 0 || !isEndPunctuation((*(sentences))[i-1]); i++){
        str[i] = (*(sentences))[i];
    }
    /* If there is another sentence, point to it now */
    if(((int) strlen(*sentences) > i+1))
        *sentences = &(*(sentences))[i+1];
    else
        *sentences = NULL;

    return str;
}

/**
 * This function checks if the characters is a letter
 *
 * @param a The character
 * @return 1 if a letter, 0 otherwise
 */
int isLetter(char a){

    if(a >= 65 && a <= 90 || a >= 97 && a <= 122)
        return 1;
    else
        return 0;
}

/**
 * This function checks if the character is an end punction
 * @param a The character
 * @return 1 if '.', '!' or '?', 0 otherwise
 */
int isEndPunctuation(char a){
    if(a == 33 || a == 63 || a == 46)
        return 1;
    else
        return 0;

}




