#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


static const int PEG_HOLES = 4;
static const char CORRECT_ANSWER = 'B';
static const char GUESS_PRESENT = 'W';
static const char INCORRECT_GUESS = '_';
static const char COLOURS[] = "ROYGBVI ";
int MAX_GUESSES;
int MAX_GUESSES_ACTUAL;
char difficultySetting;

/*void easyDifficulty()
{
    printf("\nEasy Version");
}
void mediumDifficulty()
{
    printf("\nMedium Version");
}
void hardDifficulty()
{
    printf("\nDifficult version");
}

 char getDifficulty()
 {
		printf("Which difficulty will you choose:\n");
		printf("a) Easy \n");
		printf("b) Medium \n");
		printf("c) Hard \n");

		scanf("%c", &difficultySetting);
 }

 * I wasn't able to get the difficulty setting working without affecting other parts of the code.

*/

int getMaxGuesses(){

    printf("Enter the Maximum number of guesses allowed,(Maximum of 15!):   ");
    scanf("%d",&MAX_GUESSES);
    while(true)
    if(MAX_GUESSES<=15)
    {
    printf("Number of guesses permitted: %d\n", MAX_GUESSES);
    MAX_GUESSES_ACTUAL = MAX_GUESSES-1;
    return 0;
    }
    else
    {
    printf("Too easy!Enter the Maximum number of guesses allowed,must be LESS THAN 16!): ");
    scanf("%d",&MAX_GUESSES);
    }
}

void mastermindRules() {
    printf("********************************************************************************\n");
    printf("                 Welcome to Ryan Burn's Mastermind.\n");
    printf("\tI will pick 4 letters out of a possible %d colours, and a blank space.\r\n", (int) sizeof(COLOURS) - 2);
    printf("\n");
    printf("\tYou will then get %d chances to guess which letters I picked.\r\n", MAX_GUESSES);
    printf("\tOne of the possible letters could be a blank space...\n");
    printf("\tThe responses to each guess you make are:\r\n");
    printf("\n");
    printf("\t%c a White peg indicates a correct colour in the wrong position\r\n", GUESS_PRESENT);
    printf("\t%c a Black peg indicates a correct colour in the correct position\r\n", CORRECT_ANSWER);
    printf("\t%c means you got it completely wrong, and no peg is awarded..\r\n", INCORRECT_GUESS);
    printf("\r\n");
    printf("\tYou Must Enter your answer in a 'XXXX' format, which is case insensitive");
    printf("\tYou won't lose a turn for entering a guess in the wrong format\n");
    printf("\tBased on the rainbow, the available Colours are: %s\n", COLOURS);
    printf("                  Enjoy the game and good luck!!");
    printf("\r\n");
    printf("********************************************************************************\n");

}

void makeSolution(char *solution, size_t length) {
    int count = 0;
    size_t index;
    char colourChosen;
    char *s;
    char *full_solution;
    full_solution = solution;

    *solution = 0;

    index = (double) rand() / RAND_MAX * (sizeof COLOURS - 1); // I found this way to randomly generate numbers on a C tutorial website
    while(count < length) {
        index = (double) rand() / RAND_MAX * (sizeof COLOURS - 1);
        colourChosen = COLOURS[index];
        s = strchr(full_solution, colourChosen); //compare strings
        if (s == NULL) {
            *solution = colourChosen;
            solution++;
            *solution = 0;
            count++;
        }
    }
}

char *haveAGuess(int length) {
    char line[1024];
    char *eof;
    char *userAnswer = malloc(length + 2);
    char *user_response;
    user_response = userAnswer;

    line[0] = 0;
    line[sizeof(line)-1] = 1;

    printf("Enter your guess (pick %d): ", PEG_HOLES);
    eof = fgets(line, sizeof(line), stdin); // Reads user input
    int i = 0;

    for (i = 0; i < length; i++) {
        *user_response = toupper(line[i]); // Prevents errors due to case sensitivity, again I found something similar online.
        user_response++;
    }

    *user_response = line[length + 1]; // Checks if the user entered too many letters
    user_response++;
    *user_response = 0;

    return userAnswer;
}

bool isValidGuess(char *guess) {
    char *s;
    char *user_guess;
    user_guess = guess;
    int i = 0;

    for (i = 0; i < PEG_HOLES; i++) {
        s = strchr(COLOURS, *user_guess);
        if (s == NULL) {
            return false;
        }
        user_guess++;
    }

    if (*user_guess != 0) {
        return false;
    }

    return true;
}


char *getGuess(int length) {
    char *guess = haveAGuess(length);

    while (isValidGuess(guess) == false) {
      //  printf("You can only enter the characters given.\r\n");
        free(guess);
        guess = haveAGuess(length);
    }

    return guess;
}


char *analyzeGuess(char *solution, char *guess) {
    char *result = malloc(PEG_HOLES + 1);
    char *user_result;
    char *solution_bookmark;
    char *search;
    solution_bookmark = solution;
    user_result = result;
    int i = 0;

    for (i = 0; i < PEG_HOLES; i++) {
        search = strchr(solution_bookmark, *guess);

        if (*solution == *guess) {
            *result = CORRECT_ANSWER;
        }
        else if (search != NULL) {
            *result = GUESS_PRESENT;
        }
        else {
            *result = INCORRECT_GUESS;
        }

        result++;
        guess++;
        solution++;
    }

    *result = 0;
    return user_result;
}

int main( int argc, const char* argv[] )
{
    srand(time(NULL));
    getMaxGuesses();
  //  char difficulty[11] = {'D','i','f','f','i','c','u','l','t','y','\0'};
    //getDifficulty();
    mastermindRules();

    char *solution = (char *)malloc((PEG_HOLES+1)*sizeof(char));
    makeSolution(solution, PEG_HOLES);
    int guesses = 0;
    char *guess;

    while(true)
    {
    if (guesses > MAX_GUESSES_ACTUAL) {
        printf("You've ran out of guesses! Better luck next time!\r\n");
        break;
    }

    guess = getGuess(PEG_HOLES);

    if (strcmp(solution, guess) == 0) {
        printf("\r\n");
        printf("You've guessed correctly, you win!\r\n");
        break;
    }

    printf("Result: %s\n", analyzeGuess(solution, guess));
    printf("\n\n");

    guesses++;

    }// end while

    FILE *f = fopen("HighScore.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n"); //File Reading error handling
        exit(1);
    }

// Records the last users score and name
    char userName[50];
    long elapsed_seconds;
    printf("Enter Name: ");
    scanf("%s", userName);
    fprintf(f, "Player's Name: %s\n", userName);
    fprintf(f, "Number of Guesses: %d\n", guesses+1);
    fclose(f);

  /* f = fopen ("HighScore.txt", "rt");  /* open the file for reading
   while(fgets(userName, 50, f) != NULL)
   {
	 sscanf (userName, "%c");
	 /* convert the string to a long int
	 printf ("%ld\n", );
   }
   fclose(f);   close the file  */  //I made several different attempts to be able to search through high score table but I failed.

} //End Main

