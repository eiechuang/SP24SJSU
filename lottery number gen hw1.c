#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
void generateLotteryNumbers(int numbersToGenerate, int maxNumber, int maxPowerBallNumber, int PowerBallIncluded) {
    for (int i = 0; i < numbersToGenerate; i++) {
        printf("%d", rand() % maxNumber + 1);  // Generate a random number between 1 and maxNumber
        if (i < numbersToGenerate - 1) {
            printf(", ");
        }
    }

    if (PowerBallIncluded) { //check if power ball was skipped or not
        printf(" - PowerBall: %d", rand() % maxPowerBallNumber + 1);  //powerball
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s -n NumbersToGenerate -r MaxNumber [-p MaxPowerBallNumber] -N NumberSetsToGenerate\n", argv[0]);
        return 1;
    }

    int numbersToGenerate = 0, maxNumber = 0, maxPowerBallNumber = 0, numberSetsToGenerate = 0;
    int PowerBallIncluded = 0;

    // parsing the command line commands such as -n
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            numbersToGenerate = atoi(argv[i + 1]);
            i++;  
        } else if (strcmp(argv[i], "-r") == 0) {
            maxNumber = atoi(argv[i + 1]);
            i++;
        } else if (strcmp(argv[i], "-p") == 0) {
            maxPowerBallNumber = atoi(argv[i + 1]);
            PowerBallIncluded = 1;
            i++;
        } else if (strcmp(argv[i], "-N") == 0) {
            numberSetsToGenerate = atoi(argv[i + 1]);
            i++;
        }
    }
    // Validate the input
    if (numbersToGenerate <= 0 || maxNumber <= 0 || numberSetsToGenerate <= 0 || (PowerBallIncluded && maxPowerBallNumber <= 0)) {
        printf("Invalid input. There is a number that is negative\n");
        return 1;
    }

    // random number generator
    srand(time(NULL));

    // generate
    for (int i = 0; i < numberSetsToGenerate; i++) {
        
        generateLotteryNumbers(numbersToGenerate, maxNumber, maxPowerBallNumber, PowerBallIncluded);


    }

    return 0;
}
