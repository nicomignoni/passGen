#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sodium.h>
#define INPUTLIMIT 2048 // Max string lenght in prompt

/* Parses the input string checking that only digits are in it. Transpose each 
   char digit to get the int they represent. The digit gets multiplied by the 
   respective decimal place and added to the result */
int parsedPassLenght(char string[]) {
	int result = 0;
	int decimalPlace = 1;
	int lenght = strlen(string) - 1; //  -1? Maybe reads '\n'
	for (int i = lenght - 1; i >= 0; i--) {
		if (isdigit(string[i])) {
			result += decimalPlace * (string[i] - 48); // ASCII/UTF-8 (48 to 57)
			decimalPlace *= 10;
		} else {
			return 0;
		}
	}
	return result;
}

/* Parses the Yes or No user response to ensure that it is only a y/n answer*/
char parsedYesOrNo(char string[]) {
	int lenght = strlen(string) - 1; // -1? Maybe reads '\n'
	if ((lenght == 1) & ((string[0] == 'y') | (string[0] == 'n'))) {
		return string[0];
	} else {
		return '\0';
	}
}

/* Main loop*/
void main() {
	int  passLenght;
	char input[INPUTLIMIT];
	char needPassword = 'y';
	char symbols[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 
		'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'@', '?', '!', '#', '*', '$', '\0'};
	int numSymb = strlen(symbols);

	printf("== PassGen == \n");

	do {
		/* Asks for password lenght until correct input */
		do {
			printf("passgen > Enter password lenght: ");
			fgets(input, INPUTLIMIT, stdin);
			passLenght = parsedPassLenght(input);
		} while (passLenght == 0);

		/* Prints a randomly generated password */
		printf("passgen > Password: ");
		for (int i = 0; i < passLenght; i++) {
			printf("%c", symbols[randombytes_uniform(numSymb)]);
		}
		printf("\n");

		/* Ask user for new password */
		do {
			printf("passgen > New password? [y/n] ");
			fgets(input, INPUTLIMIT, stdin);
			needPassword = parsedYesOrNo(input);
		} while (needPassword == '\0');
	  } while (needPassword == 'y');
	return;
}
