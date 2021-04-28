/**
 * The User program will prompt the user for commands to send to the Text-Manager through a
 * message queue. It will then prompt the user to provide any additional input to send. It will
 * then print to the console any information that the Text-Manager sent back to the user. The
 * program will terminate on the "exit" command.
 *
 * @author Emma Boualy
 * @studentNumber 101073617
 */

#include "shared.h"

static Message message;
char line[MAX_TEXT];

void scanInput(FILE *file);

/**
 * Main function of the user program
 * @param argc
 * @param argv test - if using the supplied input textfiles "appendTest", "removeTest",
 *                    "deleteTest", "searchTest" or "allTest"
 */
int main(int argc, char *argv[]) {

    /*If cmd line arg test used then program reads in from input file.
      No need for you to type anything in :) */
    FILE *file = NULL;
    if (argc > 1 && strcmp(argv[1], "appendTest") == 0) {
        file = fopen("inputTest1.txt", "r");
    }else if (argc > 1 && strcmp(argv[1], "deleteTest") == 0) {
        file = fopen("inputTest2.txt", "r");
    }else if (argc > 1 && strcmp(argv[1], "removeTest") == 0) {
        file = fopen("inputTest3.txt", "r");
    }else if (argc > 1 && strcmp(argv[1], "searchTest") == 0) {
        file = fopen("inputTest4.txt", "r");
    }else if (argc > 1 && strcmp(argv[1], "allTest") == 0) {
        file = fopen("inputTest5.txt", "r");
    }

    /* Instantiate and create the textManager and user message queues
       message */
    int toTextManagerQueue = createMsgQueue(TEXT_MANAGER_KEY);
    int toUserQueue = createMsgQueue(USER_KEY);
    /* Program terminates when user types "exit" as command */
    int running = 1;
    while (running) {
        /* Prompt the user to enter a command */
        printf("Enter a command call: ");
        scanInput(file);
        sendMsg(toTextManagerQueue, message);

        /* Append command sent, now prompt user for sentence to send to Text-Manager */
        if (strncasecmp(message.sentence, "append", 6) == 0) {
            printf("Enter a sentence to append to Text-Manager: ");
            scanInput(file);
            sendMsg(toTextManagerQueue, message);
        }
        /* Delete command sent, now prompt user for word to send to Text-Manager */
        else if (strncasecmp(message.sentence, "delete", 6) == 0) {
            printf("Enter a word to delete from Text-Manager: ");
            scanInput(file);
            sendMsg(toTextManagerQueue, message);
        }
        /* Remove command sent, now prompt user for word to send to Text-Manager */
        else if (strncasecmp(message.sentence, "remove", 6) == 0) {
            printf("Enter a word to remove the first sentence containing the word from Text-Manager: ");
            scanInput(file);
            sendMsg(toTextManagerQueue, message);
        }
        /* Search command sent, now prompt user for word to send to Text-Manager */
        else if (strncasecmp(message.sentence, "search", 6) == 0) {
            printf("Enter a word to search for in Text-Manager: ");
            scanInput(file);
            sendMsg(toTextManagerQueue, message);
            /* Receive and print the sentence that contains the word! */
            char *sentence = receiveMsg(toUserQueue);
            printf("Text manager returned the following sentence\n%s\n", sentence);
        }
        /* Exit command sent, terminate program. Text-Manager will take care of deleting message queues */
        else if (strncasecmp(message.sentence, "exit", 6) == 0) {
            running = 0;
        }
        /* If not a recognizable command then display expected commands to user */
        else {
            printf("Recognized commands are <append>, <delete>, <remove>, <search>, <exit>\n");
        }
    }
}

/**
 * This function will get the next input. If a text file is provided it will read from it
 * otherwise it will prompt the user for the next input to send to the Text-Manager
 *
 * @param file The file to read inputs in from, is NULL if none.
 */
void scanInput(FILE *file) {
    /* If no input file is given then prompt user for text */
    if (file == NULL) {
        char *buffer = malloc(sizeof(char) * MAX_TEXT); //allocate space to store input text
        fgets(buffer, MAX_TEXT, stdin);
        if ((strlen(buffer) > 0) && (buffer[strlen(buffer) - 1] == '\n')) //remove newline
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(message.sentence, buffer); //Copy the input into the message struct to send to text-manager
        free(buffer); //deallocate buffer, its time has come and it will be missed
    }
    else { //There is a file provided
        fgets(line, sizeof(line), file); //Read in next line of file
        if ((strlen(line) > 0) && (line[strlen(line) - 1] == '\n')) //Remove endline character
            line[strlen(line) - 1] = '\0';
        printf("%s\n", line); //Print the line to simulate the user typing it un
        strcpy(message.sentence, line); //Copy the line into the message struct to send to text-manager
    }
}