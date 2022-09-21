#include <stdio.h>
#include <string.h>

int main() {
	char secretWord[20];
	sprintf(secretWord, "MELANCIA");

	int correct = 0;
	int hanged = 0;

	char kicks[26];
	int tries = 0;

	do {
		// start the game!!!
		for(int i = 0; i < strlen(secretWord); i++) {
			int found = 0;
			for(int j = 0; j < tries; j++) {
				if(kicks[j] == secretWord[i]) {
					found = 1;
					break;
				}
			}

			if(found) {
				printf("%c ", secretWord[i]);
			} else {
				printf("_ ");
			}
		}
		printf("\n");

		char guess;
		scanf(" %c", &guess);

		kicks[tries] = guess;
		tries++;

	} while(!correct && !hanged);
}