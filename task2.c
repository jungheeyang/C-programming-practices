//
// Created by Junghee Kat Yang on 2019-05-08.
//

#include "task2.h"
#include "task1.h"

void task2(FILE *fp, char *fname) {

    HistogramTemp *results=task1(fp, fname), *temp = results;

    Matrix *matrix, *matrixHeadTemp=NULL, *matrixHead=NULL;
    Element *element, *elementHeadTemp1=NULL, *elementHeadTemp2=NULL, *elementHead=NULL;

    int **hello;
    int numRows, numCols;

    int histogramSize=1;
    int lineNum = 1;
    int findResult = 0;

    char currentline[2000];


    if(fp == NULL){
        printf("\n\n!! Error in opening file !!\n");
        printf("Program will proceed with defult 'australia.txt' file. \n");

        FILE *defultFp;
        defultFp = fopen("/Users/katyang/CLionProjects/untitled8/australia.txt", "r");

        fp = defultFp;

    }

    else {

        int sizeOfHistogram = countHistogram(temp);
        numRows = sizeOfHistogram;


//        hello = (int**)malloc(numRows* sizeof(int*));
//        numCols=numRows; // same as numRows
//
//        for (int i = 0; i < numRows ; i++) {
//            hello[i] = (int*)malloc(numCols* sizeof(int));
//        }
//
//        for (int i = 0; i <  numRows; i++){
//            for (int j = 0; j < numCols; j++){
//                hello[i][j] = 0;
//            }
//        }


//        printMatrix(hello, numRows,numCols);  // works!

        // while read test file sentence by sentence, find the words in Histogram, /
        // save it in Element struct with its line number

        while (fgets(currentline, 2000, fp)) { // 2000 << need to work out how to find the number of sentences
            temp=results;
            while(temp != NULL){
                if ((strstr(currentline, temp->words)) != NULL){

                    // save the word with its lineNumber in Element struct
                    element = malloc(sizeof(Element));
                    element->word = temp->words;
                    element->elementLineNum = lineNum;

                    //insert in head
                    element->next = elementHead;
                    elementHead = element;

                    findResult++;
                }
                temp = temp->next;
                histogramSize++;
            }
            lineNum++;
        }
        if(findResult == 0) {
            printf("\nSorry, couldn't find a match.\n");
        }
    }

    elementHeadTemp1 = elementHead;
    while(elementHeadTemp1!=NULL){

        elementHeadTemp2 = elementHead;
        while(elementHeadTemp2!=NULL){

            int flag=0; // if the matrix is existed

            // when the certain line number is finished, /
            // make elementHeadTemp2 LineNumber sync to elementHeadTemp1 LineNumber

            while(elementHeadTemp1->elementLineNum < elementHeadTemp2->elementLineNum){
                elementHeadTemp2 = elementHeadTemp2->next;
            }

            matrixHeadTemp = matrixHead;
            if (elementHeadTemp1->elementLineNum == elementHeadTemp2->elementLineNum){
                while(matrixHead != NULL){
                    if(strcmp(elementHeadTemp1->word,matrixHead->FirstWord)==0 && \
                    strcmp(elementHeadTemp2->word,matrixHead->SecondWord)==0){
                        matrixHead->count++;
                        flag++;
                        matrixHead=matrixHead->next;
                    }else{
                        matrixHead=matrixHead->next;
                        continue;
                    }
                }

                // if it's new pair, add to the matrix
                if((matrixHead == NULL)&&(flag==0)){
                    matrixHead = matrixHeadTemp;

                    matrix = malloc(sizeof(Element));
                    matrix->FirstWord = elementHeadTemp1->word;
                    matrix->SecondWord = elementHeadTemp2->word;
                    matrix->count = 1;

                    //insert in head
                    matrix->next = matrixHead;
                    matrixHead = matrix;
                }else{
                    matrixHead = matrix;
                }
            }
            elementHeadTemp2 = elementHeadTemp2->next;

            if(elementHeadTemp2 == NULL || elementHeadTemp2->elementLineNum != elementHeadTemp1->elementLineNum){
                break;
            }
        }
        elementHeadTemp1=elementHeadTemp1->next;

        if((elementHeadTemp1==NULL) && (elementHeadTemp2 == NULL))
            break;

    }

    temp = results;

//    addValueToMatrix(matrixHead, temp, hello);

    Matrix *matrixNode = matrixHead;
    HistogramTemp *resultsHead = temp;

    while(matrixNode!=NULL){
        int row=0, column=0;
        while(resultsHead != NULL){
            if(strcmp(matrixNode->FirstWord,resultsHead->words)==0){
                break;
            }
            row++;
            resultsHead = resultsHead->next;
        }

        while(resultsHead != NULL){
            if(strcmp(matrixNode->SecondWord,resultsHead->words)==0){
                break;
            }
            column++;
            resultsHead = resultsHead->next;
        }

        hello[row][column] = matrixNode->count;
        matrixNode = matrixNode->next;
    }


    hello = (int**)malloc(numRows* sizeof(int*));
    numCols=numRows; // same as numRows

    for (int i = 0; i < numRows ; i++) {
        hello[i] = (int*)malloc(numCols* sizeof(int));
    }

    for (int i = 0; i <  numRows; i++){
        for (int j = 0; j < numCols; j++){
            hello[i][j] = 0;
        }
    }

    createNewTask2File(fname, hello, numRows, numCols, temp);


    for (int j = 0; j < numRows ; j++) {
        free(hello[j]);
    }

    free(hello);
    free(elementHead);
    free(matrixHead);


    fclose(fp);
}

void printMatrix(int **array, int rows, int cols, FILE *fp, HistogramTemp *head){

    HistogramTemp *node = head;
    for (int i = 0 ; i < rows ; i++) {
        fprintf(fp, "%7s\t", node->words);
        for (int j = 0; j < cols ; j++) {
            fprintf(fp,"%d\t\t", array[i][j]);
        }
        node = node->next;
        puts("\n");
    }
}
void createNewTask2File(char *userFilename, int **array, int rows, int cols, HistogramTemp *head){

    // Create a new file name

    char *token;
    char *fullPath[20];
    char origianlFileName[20];

    token = strtok(userFilename, "/\\.");

    int i=0;
    while(token != NULL){
        fullPath[i] = token = strtok(NULL, "/\\.");
        i++;
    }
    strcpy(origianlFileName, fullPath[i-3]);
    char *newFilename = strcat(fullPath[i-3], ".correlation.txt");


    // creating a new correlation text file
    FILE *fp;
    fp = fopen(newFilename, "w");
    HistogramTemp *node = head;
    fprintf(fp, "\nInput File: %s.txt\n\n", origianlFileName );
    fprintf(fp, "\t");
    while(node!=NULL){
        fprintf(fp, "%7s\t", node->words);
        node = node->next;
    }

    printMatrix(array, rows, cols, fp, head);

    fclose(fp);
}


void addValueToMatrix(Matrix *matrixHead, HistogramTemp *results, int **hello){
    Matrix *matrixNode = matrixHead;
    HistogramTemp *resultsHead = results;

    while(matrixNode!=NULL){
        int row=0, column=0;
        while(resultsHead != NULL){
            if(strcmp(matrixNode->FirstWord,resultsHead->words)==0){
                break;
            }
            row++;
            resultsHead = resultsHead->next;
        }

        while(resultsHead != NULL){
            if(strcmp(matrixNode->SecondWord,resultsHead->words)==0){
                break;
            }
            column++;
            resultsHead = resultsHead->next;
        }

        // I dont know why it wouldnt work
        int x=matrixNode->count;
        hello[row][column]=x;
        matrixNode = matrixNode->next;
    }
}
void printElement(Element *elementHead){
    Element *node = elementHead;
    while(node!=NULL){
        printf("%d\t\t%s\n",node->elementLineNum, node->word);
        node = node->next;
    }
}
void printResult(Matrix *head){
    Matrix *node = head;
    Matrix *number = head;
    printf("\t");

    // first row
    while (node!=NULL){
        printf("%s\t", node->FirstWord);
        node=node->next;
    }
}
