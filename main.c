#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_SIZE 30
#define MAX_NUM_PEGS 4
#define MAX_TYPE_PEGS 7
//#define MAX_GUESSES 10
#define MAX_HIGH_SCORES 99
#define TRUE 1
#define FALSE 0

typedef int boolean;

// Declare functions
int ShowMenu();
int GetUserMenuOption();
int MenuPlayGame();
int MenuHighScores();
int PrintHighScores(int, int);
int MenuHelp();

int main() {

	ShowMenu();
	return 0;
}

int ShowMenu() {
printf("Welcome to Mastermind")
	GetUserMenuOption();

	return 0;
}

// Print the menu, and go to whichever
// function corresponds to the user's choice.
int GetUserMenuOption() {

	char cMenuChoice;
    fflush(stdin);

    printf("\n******\n");
	printf("*MENU*\n");
	printf("******\n\n");
	printf("1: Play game\n");
	printf("2: High scores\n");
	printf("3: Help\n");
	printf("4: Exit\n\n");
	printf("Enter your choice: ");

	fflush(stdin);
	scanf("%c", &cMenuChoice);
	fflush(stdin);

	while (cMenuChoice < 49 || cMenuChoice > 52) {

	    fflush(stdin);

		printf("\nERROR: Invalid entry\n\n");
		printf("\n******\n");
        printf("*MENU*\n");
        printf("******\n\n");
        printf("1: Play game\n");
        printf("2: High scores\n");
        printf("3: Help\n");
        printf("4: Exit\n\n");
        printf("Enter your choice: ");

        fflush(stdin);
        scanf("%c", &cMenuChoice);
        fflush(stdin);
	}

	switch (cMenuChoice) {

		case '1':
			MenuPlayGame();
			break;
		case '2':
			MenuHighScores();
			break;
      case '3':
        MenuHelp();
        break;
		case '4':
      	return 0;
			break;
		default:
			printf("\nERROR. Wrong value passed to switch.\n");

	}

	return 0;
}

// Generate the pegs &
// play the game.
int MenuPlayGame() {

    int  Max_guesses, iPegGenerationCnt, iWhitePegCnt, iBlackPegCnt, iGuessCnt, iWhitePegAmount, iBlackPegAmount, iRandomNo, iPrintAnswerCnt, iArInitCnt;
    char cViewAnswerOption, cUserOption;
    char sUserPegs[MAX_NUM_PEGS];
    char sGeneratedPegs[MAX_NUM_PEGS];
    char sUserBWPegs[MAX_NUM_PEGS];
    char sGeneratedBWPegs[MAX_NUM_PEGS];
    char sUsername[MAX_NAME_SIZE];
    FILE *fHighScores;
    boolean bGameWon = FALSE;

    iGuessCnt = iBlackPegAmount = iWhitePegAmount = 0;



		printf("Type in a number \n");
		scanf("%d", &Max_guesses);
		printf("The number you typed was %d\n", Max_guesses);

    srand (time(NULL));

    for (iPegGenerationCnt = 0; iPegGenerationCnt < MAX_NUM_PEGS; iPegGenerationCnt++) {

        iRandomNo = rand() % MAX_TYPE_PEGS;

        switch (iRandomNo) {

            case 0:
                sGeneratedPegs[iPegGenerationCnt] = 'r';
                break;

            case 1:
                sGeneratedPegs[iPegGenerationCnt] = 'o';
                break;

            case 2:
                sGeneratedPegs[iPegGenerationCnt] = 'y';
                break;

            case 3:
                sGeneratedPegs[iPegGenerationCnt] = 'g';
                break;

            case 4:
                sGeneratedPegs[iPegGenerationCnt] = 'b';
                break;

            case 5:
                sGeneratedPegs[iPegGenerationCnt] = 'v';
                break;

            case 6:
                sGeneratedPegs[iPegGenerationCnt] = 's';
                break;
        }
    }

    while ((iGuessCnt < MAX_GUESSES) && (bGameWon == FALSE)) {

        iBlackPegAmount = 0;
        iWhitePegAmount = 0;

        for (iArInitCnt = 0; iArInitCnt < MAX_NUM_PEGS; iArInitCnt++) {

            sUserPegs[iArInitCnt] = ' ';
            sGeneratedBWPegs[iArInitCnt] = ' ';
            sUserBWPegs[iArInitCnt] = ' ';
        }

        printf("\nEnter guess %d (r/o/y/g/b/v/s): ", iGuessCnt+1);
        scanf("%s", sUserPegs);

        for (iBlackPegCnt = 0; iBlackPegCnt < MAX_NUM_PEGS; iBlackPegCnt++) {

            if (sUserPegs[iBlackPegCnt] == sGeneratedPegs[iBlackPegCnt]) {

                sUserBWPegs[iBlackPegCnt] = 'b';
                sGeneratedBWPegs[iBlackPegCnt] = 'b';
                iBlackPegAmount++;
            }

            else {

                for (iWhitePegCnt = 0; iWhitePegCnt < MAX_NUM_PEGS; iWhitePegCnt++) {

                    if ((sUserPegs[iBlackPegCnt] == sGeneratedPegs[iWhitePegCnt])) {

                        if ((sUserBWPegs[iBlackPegCnt] != 98) && (sUserBWPegs[iBlackPegCnt] != 119) && (sGeneratedBWPegs[iWhitePegCnt] != 98) && (sGeneratedBWPegs[iWhitePegCnt] != 119)) {

                            sUserBWPegs[iBlackPegCnt] = 'w';
                            sGeneratedBWPegs[iWhitePegCnt] = 'w';
                            iWhitePegAmount++;
                        }
                    }
                }
            }
        }

        // If there are 4 black pegs,
        // then the game is won.
        if (iBlackPegAmount == 4) {

            bGameWon = TRUE;
            printf("\nYou win!\n");
            printf("\nEnter your name to record your score (no spaces!): ");
            scanf("%s", sUsername);

            fHighScores = fopen("scores.dat", "a");
            fprintf(fHighScores, "%s %d\n", sUsername, iGuessCnt+1);
            fclose(fHighScores);
            GetUserMenuOption();
        }

        else {

            iGuessCnt++;
        }

        // Print the black and white pegs that
        // the user has been awarded.
        while ((iBlackPegAmount > 0) || (iWhitePegAmount > 0)) {

            if (iBlackPegAmount != 4) {
                if (iBlackPegAmount > 0) {
                    printf("B");
                    iBlackPegAmount--;
                }

                else if (iWhitePegAmount > 0) {
                    printf("W");
                    iWhitePegAmount--;
                }
            }
        }

        printf("\n");

    }

    if (bGameWon == FALSE) {

        // Give the user the option of viewing the combination that
        // they failed to crack.
        printf("\nYou lost!\nWould you like to see the uncracked combination? (Y/N): ");
        scanf("%c", &cViewAnswerOption);

        while ((cViewAnswerOption != 89) && (cViewAnswerOption != 78) && (cViewAnswerOption != 110) && (cViewAnswerOption != 121)) {

            fflush(stdin);
            printf("\nERROR: Invalid Entry.\n");
            printf("\nWould you like to see the uncracked combination? (Y/N): ");
            scanf("%c", &cViewAnswerOption);
        }

        if ((cViewAnswerOption == 89) || (cViewAnswerOption == 121)) {

            printf("\nThe winning combination is: ");

            for (iPrintAnswerCnt = 0; iPrintAnswerCnt < MAX_NUM_PEGS; iPrintAnswerCnt++) {

                printf("%c", sGeneratedPegs[iPrintAnswerCnt]);
            }
        }

        // Ask the user if they want to return to
        // the menu after a game. If not, exit the program.
        do {

            printf("\n\nReturn to menu? (Y/N): ");
            scanf("%c", &cUserOption);
        } while((cUserOption != 'y') && (cUserOption != 'n') && (cUserOption != 'N') && (cUserOption != 'Y'));

        if ((cUserOption == 'y') || (cUserOption == 'Y'))
            GetUserMenuOption();

        else
            return 0;
    }

}

// Print the high scores that have been recorded,
// from lowest # of guesses to highest.
int MenuHighScores() {

    FILE *fScores;
    char sNames[MAX_HIGH_SCORES][MAX_NAME_SIZE], cUserOption;
    int iArrayDataEntryCnt, iScore[MAX_HIGH_SCORES], iValidHighScoreCnt=0, iCnt3, iCnt4=0, iCnt5, iNumberPrintCnt=0;

    fScores = fopen("scores.dat", "r");

    for (iArrayDataEntryCnt = 0; iArrayDataEntryCnt < MAX_HIGH_SCORES; iArrayDataEntryCnt++) {
        fscanf(fScores, "%s", &sNames[iArrayDataEntryCnt]);
        fscanf(fScores, "%d", &iScore[iArrayDataEntryCnt]);

        if ((strcmp(sNames[iArrayDataEntryCnt], "")) == 0)
            break;

        else
            iValidHighScoreCnt++;
    }

    for (iCnt3 = 0; iCnt3 < MAX_GUESSES; iCnt3++) {

        iCnt4++;

        for (iCnt5=0; iCnt5<iValidHighScoreCnt; iCnt5++) {

            if ((iScore[iCnt5] == iCnt4)) {
                iNumberPrintCnt++;
                printf("%d. %s\t%d tries\n", iNumberPrintCnt, sNames[iCnt5], iScore[iCnt5]);
            }

        }

    }

    // Ask the user if they want to return to
    // the menu after a game. If not, exit the program.
    do {

        printf("\n\nReturn to menu? (Y/N): ");
        scanf("%c", &cUserOption);
    } while((cUserOption != 'y') && (cUserOption != 'n') && (cUserOption != 'N') && (cUserOption != 'Y'));

    if ((cUserOption == 'y') || (cUserOption == 'Y'))
        GetUserMenuOption();

    else
        return 0;
}

// Print instructions on how to play
// the game to the screen.
int MenuHelp() {

    char cUserOption;

    printf("Welcome to Mastermind!\n\n");
    printf("The goal of this game is to guess the correct combination of coloured pegs that are randomly generated each and every time you start a new game of Mastermind.");
    printf("The colours that can be generated are red, orange, yellow, green, blue and violet. Spaces can also be generated.\n\n");
    printf("Enter your guess as four lowercase letters when you are asked to do so (eg. 'r' for red, 'g' for green, 's' for space, etc.). ");
    printf("You will be awarded for black and white pegs for your guess. A black peg means that you have placed a peg of the right colour (or a space) in the right location,");
    printf("and a white peg means that you have placed a peg of the right colour (or a space) in an incorrect location. Use logic and cunning to crack the combination!\n\n");
    printf("Good luck!");

    do {

        printf("\n\nReturn to menu? (Y/N): ");
        scanf("%c", &cUserOption);
    } while((cUserOption != 'y') && (cUserOption != 'n') && (cUserOption != 'N') && (cUserOption != 'Y'));

    if ((cUserOption == 'y') || (cUserOption == 'Y'))
        GetUserMenuOption();

    else
        return 0;
}

