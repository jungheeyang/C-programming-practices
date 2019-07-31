#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "task1.h"
#include "task2.h"


int main() {

    FILE *fp;
    char *fname = malloc(sizeof(char));
    printf("\n\n:::::::::::::: TASK 1 ::::::::::::::\n\nPlease Enter the Full Path of the file: \n");
    scanf("%s", fname);
    fp = fopen( fname , "r");

    task1(fp, fname);
    HistogramTemp *uniqueWordTempHead = task1(fp, fname);
    task2(fp, fname);



    free(fname);
    free(uniqueWordTempHead);
    return 0;

}

