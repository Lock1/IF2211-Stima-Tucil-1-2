// Tugas kecil 1

#define BUFFER_SIZE 16
#define MAX_OPERAND 8

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int stringLength(char* string) {
    int count = 0, i = 0;
    while (string[i] != '\0' && string[i++] != '\r')
        count++;
    return count;
}

int main(int argc, char const *argv[]) {
    FILE* filePtr = fopen(argv[1],"r");
    struct timespec start, stop;
    char operand[MAX_OPERAND][BUFFER_SIZE], sum[BUFFER_SIZE], buffer[BUFFER_SIZE];
    int operandCount = 0;

    // Argument Checking
    if (argc < 2) {
        fprintf(stderr, "Usage : ./main <filename>\n");
        exit(1);
    }

    // File processing
    puts("===================");
    puts("Input :");
    while (fgets(buffer, BUFFER_SIZE, filePtr)) {
        printf("%s", buffer);
        if (buffer[0] != '-') {
            strcpy(operand[operandCount], buffer);
            operandCount++;
        }
        else {
            if (fgets(buffer, BUFFER_SIZE, filePtr))
                strcpy(sum, buffer);
            printf("%s", sum);
            puts("\n");
            break;
        }
    }

    // Main Algorithm
    if (operandCount > 1) {
        // Strip plus sign
        operand[operandCount - 1][stringLength(operand[operandCount - 1]) - 1] = '\0';

        // Array Initialize
        int alphaValue[26], tempOperandSum, sumValue, isFirstChar[26];
        for (int i = 0; i < 26; i++) {
            alphaValue[i] = -1;
            isFirstChar[i] = 0;
        }

        // Finding used alphabet
        for (int i = 0; i < operandCount; i++) {
            int j = 0;
            while (operand[i][j] != '\0' && operand[i][j] != '\r') {
                int tempAlphaIndex = ((int) operand[i][j]) - 65;
                alphaValue[tempAlphaIndex] = 0;
                if (j == 0)
                    alphaValue[tempAlphaIndex] = isFirstChar[tempAlphaIndex] = 1;
                j++;
            }
        }
        int tempIdx = 0;
        while (sum[tempIdx] != '\0' && sum[tempIdx] != '\r') {
            int tempAlphaIndex = ((int) sum[tempIdx]) - 65;
            alphaValue[tempAlphaIndex] = 0;
            if (tempIdx == 0)
                alphaValue[tempAlphaIndex] = isFirstChar[tempAlphaIndex] = 1;
            tempIdx++;
        }

        // Brute forcing
        int testCount = 0, isValidCombination = 0;
        puts("Searching ...");
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

        // int operandVal[16]; // DEBUG
        do {
            sumValue = tempOperandSum = 0;

            // Temporary operand sum
            for (int i = 0; i < operandCount; i++) {
                int j = 0, operandValue = 0;
                while (operand[i][j] != '\0' && operand[i][j] != '\r') {
                    operandValue = 10*operandValue + alphaValue[((int) operand[i][j]) - 65];
                    j++;
                }
                // operandVal[i] = operandValue; // DEBUG
                tempOperandSum += operandValue;
            }

            // Temporary "Result" sum
            int a = 0;
            while (sum[a] != '\0' && sum[a] != '\r') {
                sumValue = 10*sumValue + alphaValue[((int) sum[a]) - 65];
                a++;
            }
            // printf("%d\n%d\n", sumValue,tempOperandSum); // DEBUG

            // Uniqueness test
            int isUniqueCombination = 1;
            for (int i = 0; i < 26 && isUniqueCombination; i++) {
                for (int j = i + 1; j < 26; j++) {
                    if ((alphaValue[i] >= 0) && (alphaValue[i] == alphaValue[j])) {
                        isUniqueCombination = 0;
                        break;
                    }
                }
            }

            // Solution check and solution set generator
            if (isUniqueCombination && (tempOperandSum == sumValue))
                isValidCombination = 1;
            else {
                for (int i = 0; i < 26; i++) {
                    if (9 > alphaValue[i] && alphaValue[i] >= 0) {
                        alphaValue[i]++;
                        break;
                    }
                    else if (alphaValue[i] == 9) {
                        if (isFirstChar[i])
                            alphaValue[i] = 1;
                        else
                            alphaValue[i] = 0;
                    }
                }
            }

            // if (testCount % 10000000 == 0) { // DEBUG
            //     for (int i = 0; i < operandCount; i++)
            //         printf("%4d ", operandVal[i]);
            //     printf(" %6d\n", sumValue);
            // }
            testCount++;
        } while (!isValidCombination);

        // DEBUGGING PURPOSE
        // for (int i = 0; i < 26; i++)
        //     if (!alphaValue[i])
        //         printf("%c",(char) (i + 65));


        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
        double result = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / 1e9;
        printf("Time elapsed : %f\n", result);
        printf("Total test count : %d\n", testCount);

        puts("\nResult :");
        for (int i = 0; i < operandCount; i++) {
            int j = 0, operandValue = 0;
            while (operand[i][j] != '\0' && operand[i][j] != '\r') {
                operandValue = 10*operandValue + alphaValue[((int) operand[i][j]) - 65];
                j++;
            }
            if (i != operandCount - 1)
                printf("%d\n", operandValue);
            else
                printf("%d+\n", operandValue);
        }
        puts("------");
        int a = 0;
        sumValue = 0;
        while (sum[a] != '\0' && sum[a] != '\r') {
            sumValue = 10*sumValue + alphaValue[((int) sum[a]) - 65];
            a++;
        }
        printf("%d\n\n",sumValue);

        for (int i = 0; i < 26; i++)
            if (alphaValue[i] >= 0)
                printf("%c = %d\n", (char) (65 + i), alphaValue[i]);
    }
    else
        puts("Operand less than 2");

    // For better readibily on script
    puts("===================\n");
    return 0;
}
