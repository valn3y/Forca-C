#include <stdio.h>
#include <string.h>
#include "forca.h"

char secretWord[20];
char kicks[26];
int givenKicks = 0;


void opening() {
	printf("*************************\n");
	printf("*     Jogo da Forca     *\n");
	printf("*************************\n\n");
}

void actionGuess() {
	char guess;
	scanf(" %c", &guess);

	kicks[givenKicks] = guess;
	givenKicks++;
}

int alreadyGuess(char letter) {
	int found = 0;
	for(int j = 0; j < givenKicks; j++) {
		if(kicks[j] == letter) {
			found = 1;
			break;
		}
	}

	return found;
}

void choseWord() {
	sprintf(secretWord, "MELANCIA");
}

int correct() {
	for(int i = 0; i < strlen(secretWord); i++) {
		if(!alreadyGuess(secretWord[i])) {
			return 0;
		}
	}

	return 1;
}

void drawGallows() {
	// start the game!!!
	for(int i = 0; i < strlen(secretWord); i++) {
		int found = alreadyGuess(secretWord[i]);
		if(found) {
			printf("%c ", secretWord[i]);
		} else {
			printf("_ ");
		}
	}
	printf("\n");
}

int isHanged() { 
	int errors = 0;

	for(int i = 0; i < givenKicks; i++) {
		int exist = 0;
		for(int j = 0; j < strlen(secretWord); j++) {
			if(kicks[i] == secretWord[j]) {
				exist = 1;
				break;
			}
		}
		if(!exist) errors++;
	}

	return errors >= 5;
}

int main() {
	choseWord();
	opening();

	do {
		drawGallows();
		actionGuess();

	} while(!correct() && !isHanged());
}