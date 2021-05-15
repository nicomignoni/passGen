#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <sodium.h>

#define NUM_SYMBOLS 65
#define INPUT_SIZE  50 // bytes
#define PASS_SIZE   2  // bytes
#define PASS_MAX    99 // Max password lenght
#define RESP_SIZE   1  // bytes
#define YES         'y'
#define NO          'n'

bool needPassword = 1;
char passLenghtStr[INPUT_SIZE];
char YesOrNo[INPUT_SIZE];
char symbols[NUM_SYMBOLS] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@\0";

bool parseLenght(char *input) {
    int lenght = strtol(input, &input, 10);
    if (strlen(input) > PASS_SIZE + 1 || lenght > PASS_MAX || lenght == 0) {
        printf("passgen > Invalid input\n"); return 0;
    }
    return 1;
}

bool parseYesOrNo(char *input) {
    if (strlen(input) > RESP_SIZE + 1 || !(input[0] == YES || input[0] == NO)) {
        printf("passgen > Invalid input\n"); return 0;
    } else if (input[0] == YES) {
        needPassword = 1; return 1;
    } else if (input[0] == NO) {
        needPassword = 0; return 1;
    }
}

int main() {
    printf("---- passGen ----\n");
    do {
        /* Ask for a valid input (password lenght) */
        do{
            printf("passgen > Enter password lenght: ");
            fgets(passLenghtStr, INPUT_SIZE, stdin);
        } while (!parseLenght(passLenghtStr));

        /* Generate password */
        printf("passgen > Password: ");
        char *slackPtr;
        long passLenght = strtol(passLenghtStr, &slackPtr, 10);
        char indices[passLenght];
        randombytes_buf(indices, passLenght);
        for (int i = 0; i < passLenght; i++) {
            printf("%c", symbols[indices[i] % strlen(symbols)]);
        }
        printf("\n");

        /* Ask for a new password */
        do {
            printf("passgen > Need a new password? [y/n] ");
            fgets(YesOrNo, INPUT_SIZE, stdin);
        } while (!parseYesOrNo(YesOrNo));

    } while (needPassword);
}
