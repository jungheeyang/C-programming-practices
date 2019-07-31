//
// Created by Junghee Kat Yang on 2019-05-08.
//

#ifndef UNTITLED8_TASK2_H
#define UNTITLED8_TASK2_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "task1.h"

void task2(FILE *fp, char *fname);

// two words with their index
typedef struct matrix {
    char *FirstWord;
    char *SecondWord;
    int count;
    struct matrix *next;
} Matrix;

// word with its line number
typedef struct element {
    char *word;
    int elementLineNum;
    struct element *next;
} Element;
HistogramTemp *task1(FILE *fp, char *fname);

void printMatrix(int **array, int rows, int cols, FILE *fp, HistogramTemp *head);
void createNewTask2File(char *userFilename, int **array, int rows, int cols, HistogramTemp *head);




#endif //UNTITLED8_TASK2_H

