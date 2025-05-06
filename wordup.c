//Author : Ngoc Phuong Uyen Nguyen
//Date ; May 6th, 2025
//project 10

#include <stdio.h>

#define MAX_GUESSES 6
#define WORD_LENGTH 5
#define MAX_WORDS 6


void read(char word[]);
int ValidGuess(char guess[]);
void Lowercase (char str[]);
void Display(char guesses[][WORD_LENGTH + 1], int NumGuess, char mystery[]);
void Checking(char guess[], char mystery[], char result[]);
int Winning(char guess[], char mystery[]);
void Pointing(char result[]);
void Clearing(void);
int Equal(char str1[], char str2[]);

int main() {
	char mystery[WORD_LENGTH + 1];
	char guesses[MAX_GUESSES][WORD_LENGTH + 1];
	char guess[WORD_LENGTH + 1];
	int NumGuess = 0;
	int won = 0;

	read(mystery);

	while (NumGuess < MAX_GUESSES && !won) {
    	if (NumGuess == MAX_GUESSES - 1 || Winning(guess, mystery)) {
        	printf("Final Guess: ");
        	scanf("%5s", guess);
        	Clearing();

        	if (!ValidGuess(guess)) {
            	printf("Guess must be 5 letters long and contain only letters.\n");
            	continue;
        	}

        	Lowercase (guess);
       	 
        	for (int i = 0; i < WORD_LENGTH; i++) {
            	guesses[NumGuess][i] = guess[i];
        	}
        	guesses[NumGuess][WORD_LENGTH] = '\0';
       	 
        	Display(guesses, NumGuess + 1, mystery);
       	 
        	if (Winning(guess, mystery)) {
            	won = 1;
            	printf("   	%s        	\n ");
            	printf("You won in %d guess!\n", NumGuess + 1);
            	printf("   	Congratulations!\n");
        	} else {
            	NumGuess++;
            	if (NumGuess == MAX_GUESSES) {
                	printf("Good luck next time! The word was: %s\n", mystery);
            	}
        	}
    	} else {
        	printf("GUESS %d! Enter your guess: ", NumGuess + 1, MAX_GUESSES);
        	scanf("%5s", guess);
       	 
        	Clearing();
        	printf("===============================\n");

        	if (!ValidGuess(guess)) {
            	printf("Guess must be 5 letters long and contain only letters.\n");
            	continue;
        	}

        	Lowercase (guess);
       	 
        	for (int i = 0; i < WORD_LENGTH; i++) {
            	guesses[NumGuess][i] = guess[i];
        	}
        	guesses[NumGuess][WORD_LENGTH] = '\0';
       	 
        	Display(guesses, NumGuess + 1, mystery);
       	 
        	if (Winning(guess, mystery)) {
            	won = 1;
            	printf("     	%s        	\n ");
            	printf("You won in %d guess!\n", NumGuess + 1);
            	printf("  Congratulations!\n");
        	} else {
            	NumGuess++;
        	}
    	}
	}

	return 0;
}

void read(char word[]) {
	FILE *file = fopen("mystery.txt", "r");
	if (file == NULL) {
    	printf("Error opening file!\n");
    	word[0] = '\0';
    	return;
	}
	fscanf(file, "%5s", word);
	Lowercase (word);
	fclose(file);
}

int ValidGuess(char guess[]) {
	int len = 0;
	while (guess[len] != '\0') {
    	if (guess[len] < 'A' || (guess[len] > 'Z' && guess[len] < 'a') || guess[len] > 'z') {
        	return 0;
    	}
    	len++;
	}
	return len == WORD_LENGTH;
}

void Lowercase (char str[]) {
	for (int i = 0; str[i] != '\0'; i++) {
    	if (str[i] >= 'A' && str[i] <= 'Z') {
        	str[i] = str[i] + 32;
    	}
	}
}

void Display(char guesses[][WORD_LENGTH + 1], int NumGuess, char mystery[]) {
	char result[WORD_LENGTH + 1];
    
	for (int i = 0; i < NumGuess; i++) {
    	Checking(guesses[i], mystery, result);
   	 
    	for (int j = 0; j < WORD_LENGTH; j++) {
        	if (result[j] == 'C') {
            	if (guesses[i][j] >= 'a' && guesses[i][j] <= 'z') {
                	printf("%c", guesses[i][j] - 32);
            	} else {
                	printf("%c", guesses[i][j]);
            	}
        	} else {
            	printf("%c", guesses[i][j]);
        	}
    	}
    	printf("\n");
   	 
    	Pointing(result);
    	printf("\n");
	}
}

void Checking(char guess[], char mystery[], char result[]) {
	for (int i = 0; i < WORD_LENGTH; i++) {
    	if (guess[i] == mystery[i]) {
        	result[i] = 'C';
    	} else {
        	result[i] = 'N';
        	for (int j = 0; j < WORD_LENGTH; j++) {
            	if (guess[i] == mystery[j] && result[j] != 'C') {
                	result[i] = 'W';
                	break;
            	}
        	}
    	}
	}
	result[WORD_LENGTH] = '\0';
}

void Pointing(char result[]) {
	for (int i = 0; i < WORD_LENGTH; i++) {
    	if (result[i] == 'W') {
        	printf("^");
    	} else {
        	printf(" ");
    	}
	}
}

int Winning(char guess[], char mystery[]) {
	return Equal(guess, mystery);
}

void Clearing(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int Equal(char str1[], char str2[]) {
	for (int i = 0; i < WORD_LENGTH; i++) {
    	if (str1[i] != str2[i]) {
        	return 0;
    	}
	}
	return 1;
}






