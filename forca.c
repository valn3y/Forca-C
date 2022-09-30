#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

char secretWord[SIZE_WORD];
char kicks[26];
int givenKicks = 0;


void opening() {
	printf("*************************\n");
	printf("*     Jogo da Forca     *\n");
	printf("*************************\n\n");
}

void actionGuess() {
	char guess;
	printf("Qual letra? ");
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

void addWord() {
	char yesOrNo;
	printf("Voce deseja adicionar uma palavra no jogo? (S/N) ");
	scanf(" %c", &yesOrNo);

	if(yesOrNo == 'S') {
		char newWord[SIZE_WORD];
		printf("Digite a nova palavra em letras maiúsculas: ");
		scanf("%s", newWord);

		FILE* f;
		f = fopen("words.txt", "r+");
		if(f == 0) {
			printf("Banco de dados de palavras não disponível\n\n");
			exit(1);
		}

		int quantityWords;
		fscanf(f, "%d", &quantityWords);
		quantityWords++;

		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", quantityWords);

		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", newWord);
		fclose(f);
	}
}

void chooseWord() {
	FILE* f;
	f = fopen("words.txt", "r");
	if(f == 0) {
		printf("Desculpe, banco de dados não disponível\n\n");
		exit(1);
	}

	int quantityWords;
	fscanf(f, "%d", &quantityWords);

	srand(time(0));
	int random = rand() % quantityWords;

	for(int i = 0; i <= random; i++) {
		fscanf(f, "%s", secretWord);
	}

	fclose(f);
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
	int errors = wrongGuess();

	printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (errors>=1?'(':' '), (errors>=1?'_':' '), (errors>=1?')':' '));
    printf(" |      %c%c%c  \n", (errors>=3?'\\':' '), (errors>=2?'|':' '), (errors>=3?'/': ' '));
    printf(" |       %c     \n", (errors>=2?'|':' '));
    printf(" |      %c %c   \n", (errors>=4?'/':' '), (errors>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

	// start the game!!!
	for(int i = 0; i < strlen(secretWord); i++) {
		if(alreadyGuess(secretWord[i])) {
			printf("%c ", secretWord[i]);
		} else {
			printf("_ ");
		}
	}
	printf("\n");
}

int isHanged() { 
	return wrongGuess() >= 5;
}

int wrongGuess() {
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

	return errors;
}

int main() {
	opening();
	chooseWord();

	do {
		drawGallows();
		actionGuess();

	} while(!correct() && !isHanged());


	if(correct()) {
		printf("\nParabéns, você ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
	} else {
		printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", secretWord);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n\n");
	}

	addWord();
}