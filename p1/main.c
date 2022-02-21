/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL LOPEZ LOPEZ            LOGIN 1: m.llopez
 * AUTHOR 2: DANIEL FERNÁNDEZ FEÁS         LOGIN 2: daniel.fernandezf
 * GROUP: 4.4
 * DATE: ** / ** / 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif


void new(char *productId, char *userId, char *productCategory,
         char *productPrice, tList *list) {
    
}

void stats(tList list) {
    
}

void bid(char *productId, char *userId, char *productPrice, tList *list) {
    
}

void delete(char *productId, tList *list) {
    
}

void processCommand(char *commandNumber, char command, char *param1,
                    char *param2, char *param3, char *param4, tList *list) {

    printf("********************\n");

    switch (command) {
        case 'N': {
            printf("%s %c: product %s seller %s category %s price %s\n",
                   commandNumber, command, param1, param2, param3, param4);
            new(param1, param2, param3, param4, list);
            break;
        }
        case 'S': {
            printf("%s %c \n", commandNumber, command);
            stats(*list);
            break;
        }
        case 'B': {
            printf("%s %c: product %s bidder %s price %s\n",
                   commandNumber, command, param1, param2, param3);
            bid(param1, param2, param3, list);
            break;
        }
        case 'D': {
            printf("%s %c: product %s\n", commandNumber, command, param1);
            delete(param1, list);
            break;
        }
        default: {
            break;
        }
    }
}

void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    //Crear lista
    tList list;
    createEmptyList(&list);

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2,
                           param3, param4, &list);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}
