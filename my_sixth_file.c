#include "shell.h"
#include <stdlib.h>

/**
 * isDelimiter - Checks if a character is a delimiter.
 * @c: The character to check.
 * @deli: The delimiter string.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int isDelimiter(char c, char *deli) {
    while (*deli) {
        if (*deli == c) {
            return 1; // Character is a delimiter
        }
        deli++;
    }
    return 0; // Character is not a delimiter
}

/**
 * splitString - Splits a string into words. Repeat delimiters are ignored.
 * @String: The input string.
 * @deli: The delimiter string.
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **splitString(char *String, char *deli) {
    int i, j, k, m, numWords = 0;
    char **resultArray;

    if (String == NULL || String[0] == '\0') {
        return NULL;
    }

    if (!deli) {
        deli = " ";
    }

    for (i = 0; String[i] != '\0'; i++) {
        if (!isDelimiter(String[i], deli) &&
                (isDelimiter(String[i + 1], deli) || String[i + 1] == '\0')) {
            numWords++;
        }
    }

    if (numWords == 0) {
        return NULL;
    }

    resultArray = malloc((1 + numWords) * sizeof(char *));
    if (!resultArray) {
        return NULL;
    }

    for (i = 0, j = 0; j < numWords; j++) {
        while (isDelimiter(String[i], deli)) {
            i++;
        }

        k = 0;
        while (!isDelimiter(String[i + k], deli) && String[i + k] != '\0') {
            k++;
        }

        resultArray[j] = malloc((k + 1) * sizeof(char));
        if (!resultArray[j]) {
            for (k = 0; k < j; k++) {
                free(resultArray[k]);
            }
            free(resultArray);
            return NULL;
        }

        for (m = 0; m < k; m++) {
            resultArray[j][m] = String[i++];
        }
        resultArray[j][m] = '\0';
    }

    resultArray[j] = NULL;
    return resultArray;
}

/**
 * splitString2 - Splits a string into words.
 * @String: The input string.
 * @deli: The delimiter character.
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **splitString2(char *String, char deli) {
    int i, j, k, m, numWords = 0;
    char **resultArray;

    if (String == NULL || String[0] == '\0') {
        return NULL;
    }

    for (i = 0; String[i] != '\0'; i++) {
        if ((String[i] != deli && String[i + 1] == deli) ||
                (String[i] != deli && !String[i + 1]) || String[i + 1] == deli) {
            numWords++;
        }
    }

    if (numWords == 0) {
        return NULL;
    }

    resultArray = malloc((1 + numWords) * sizeof(char *));
    if (!resultArray) {
        return NULL;
    }

    for (i = 0, j = 0; j < numWords; j++) {
        while (String[i] == deli && String[i] != '\0') {
            i++;
        }

        k = 0;
        while (String[i + k] != deli && String[i + k] != '\0') {
            k++;
        }

        resultArray[j] = malloc((k + 1) * sizeof(char));
        if (!resultArray[j]) {
            for (k = 0; k < j; k++) {
                free(resultArray[k]);
            }
            free(resultArray);
            return NULL;
        }

        for (m = 0; m < k; m++) {
            resultArray[j][m] = String[i++];
        }
        resultArray[j][m] = '\0';
    }

    resultArray[j] = NULL;
    return resultArray;
}

