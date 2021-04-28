/**
 * This header file includes all the shared
 * functions and variables used in the user
 * and text-manager programs
 *
 * @author Emma Boulay
 */
#ifndef SHARED_H
#define SHARED_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/time.h>

#define MICRO_SEC_IN_SEC 1000000
#define MAX_TEXT 35 // The max length of data transferred into msg queue

int TEXT_MANAGER_KEY = 1234; //Key for toTextManager queue
int USER_KEY = 5678; //Key for toUser queue

/**
 * Message struct to be used for sending and receiving with
 * message queue
 */
typedef struct{
    long int msgType;
    char sentence[MAX_TEXT];
} Message;
static Message msg;

/**
 * A struct used to keep track of the current average
 * and the number of data points. Used to find average
 * time of each command.
 */
struct Average_t{
    float average;
    int n;
};

/**
 * This function will create a message queue from a key
 * @param key Used to create message queue
 * @return message ID
 */
int createMsgQueue(int key){
    int msgid = msgget((key_t)key, 0666 | IPC_CREAT);
    if (msgid == -1){
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    return msgid;
}

/**
 * This function will delete a message queue
 * @param msgid The message queue's ID
 */
void deleteMsgQueue(int msgid){
    if(msgctl(msgid, IPC_RMID, 0) == -1){
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * This function is used to send a message to a message queue
 * @param msgid ID of the message queue for the message to be sent to
 * @param sendMsg the message to be sent
 */
void sendMsg(int msgid, Message sendMsg){
    sendMsg.msgType = 1;
    if(msgsnd(msgid, (void *)&sendMsg, MAX_TEXT, 0) == -1){
        fprintf(stderr, "msgsnd failed\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * This function retrieves the next message from a message queue
 * @param msgid ID of the message queue for the message to be retrieved from
 * @return the next message
 */
char* receiveMsg(int msgid){

    long int msgRec = 0;
    if(msgrcv(msgid, (void *)&msg, BUFSIZ, msgRec, 0) == -1){
        fprintf(stderr, "msgrcv failed with error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    return msg.sentence;
}

#endif
