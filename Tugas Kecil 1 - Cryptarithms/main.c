// Tugas kecil 1
// Tanur Rizaldi Rahardjo / 13519214

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

    // File processing
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
            puts("\n\n");
            break;
        }
    }

    if (operandCount > 1) {
        // TBA : Source Code
    }
    else
        puts("Operand less than 2");

    return 0;
}
