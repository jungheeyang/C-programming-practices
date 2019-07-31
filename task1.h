//
// Created by Junghee Kat Yang on 2019-05-08.
//

#ifndef UNTITLED8_TASK1_H
#define UNTITLED8_TASK1_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


typedef struct histogramTemp {
    char *words;
    int count;
    struct histogramTemp *next;
} HistogramTemp;

typedef struct temp{
    char c;
    struct temp *next;
} Temp;

HistogramTemp *task1(FILE *fp, char *fname);

int countHistogram (HistogramTemp *head);
void printHistogram (HistogramTemp *head, FILE *fp);
void createNewFile(char *userFilename, HistogramTemp *head);



#endif //UNTITLED8_TASK1_H
