#include <stdio.h>
#include <string.h>

char secretWord[20];
char kicks[26];
int tries = 0;

void opening() {
	printf("*************************\n");
	printf("*     Jogo da Forca     *\n");
	printf("*************************\n\n");
}

void actionGuess() {
	char guess;
	scanf(" %c", &guess);

	kicks[tries] = guess;
	tries++;
}

int alreadyGuess(char letter) {
	int found = 0;
	for(int j = 0; j < tries; j++) {
		if(kicks[j] == letter) {
			found = 1;
			break;
		}
	}

	return found;
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

void choseWord() {
	sprintf(secretWord, "MELANCIA");
}

int main() {
	int correct = 0;
	int hanged = 0;

	choseWord();
	opening();

	do {
		drawGallows();
		actionGuess();

	} while(!correct && !hanged);
}