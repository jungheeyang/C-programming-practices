//
// Created by Junghee Kat Yang on 2019-05-08.
//
#include "task1.h"
#include "CommonWords.h"

HistogramTemp *task1(FILE *fp, char *fname){

    char textfile, *string = NULL;

    Temp *tempHead = NULL, *temp1, *temp2;
    HistogramTemp *uniqueWordTemp = NULL, *headTemp, *uniqueWordTempHead = NULL;


    if(fp == NULL){
        printf("\n\n!! Error in opening file !!\n");
        printf("Program will proceed with defult 'australia.txt' file. \n");

        FILE *defultFp;
        defultFp = fopen("/Users/katyang/CLionProjects/untitled8/australia.txt", "r");

        fp = defultFp;

    }

    while((textfile = fgetc(fp))!=EOF){

        // save temporary word as a separate char linked list 'Temp', and save it to 'string' as a whole word

        if (isupper(textfile)>0) {
            temp1 = (Temp*)malloc(sizeof(Temp));
            temp1->c = textfile;

            temp1->next = tempHead;
            tempHead = temp1;

            int i=0;
            while(tempHead != NULL){
                string = malloc(sizeof(char)+1);
                strcpy(&string[i],&tempHead->c);
                i++;
                tempHead = tempHead->next;
            }

            while ((textfile = fgetc(fp))!=EOF) {
                if (isalpha(textfile)>0 && !(isupper(textfile))) {
                    temp2 = malloc(sizeof(Temp)+1);
                    temp2->c = textfile;

                    temp2->next = tempHead;
                    tempHead = temp2;

                    while(tempHead != NULL){
                        strcpy(&string[i],&tempHead->c);
                        i++;
                        tempHead = tempHead->next;
                    }
                }

                // use 'string', make Histogram
                if(isupper(textfile) || !isalpha(textfile)){

                    int flag=0;
                    int commonWordsFlag=0;

                    // check if the words are in the commonWords list
                    for (int j = 0; j < 122 ; j++) {
                        if (strcmp(string, commonwords[j])==0){
                            commonWordsFlag++;
                            break;
                        }
                    }

                    if((strlen(string)<3) || (commonWordsFlag == 1)){
                        break;
                    }

                    headTemp = uniqueWordTempHead;

                    // compare string to uniqueWordTemp
                    while (uniqueWordTempHead != NULL){

                        // increment count if the word is in Histogram
                        if(strcmp(uniqueWordTempHead->words, string)==0){
                            uniqueWordTempHead->count++;
                            flag++;
                            uniqueWordTempHead=uniqueWordTempHead->next;
                        }else{
                            uniqueWordTempHead=uniqueWordTempHead->next;
                            continue;
                        }
                    }

                    // create new node if the word is not in Histogram
                    if ((uniqueWordTempHead == NULL) && (flag == 0)){
                        uniqueWordTempHead = headTemp;

                        uniqueWordTemp = malloc(sizeof(HistogramTemp)+1);
                        uniqueWordTemp->words = string;
                        uniqueWordTemp->count=1;

                        // insert in head
                        uniqueWordTemp ->next = uniqueWordTempHead;
                        uniqueWordTempHead = uniqueWordTemp;

                    }else{
                        uniqueWordTempHead = uniqueWordTemp;
                    }
                    break;
                }
            }
        }
    }


    createNewFile(fname, uniqueWordTempHead);

    free(string);
    free(tempHead);
    return(uniqueWordTempHead);

}

int countHistogram (HistogramTemp *head) {
    int numberOfWords=0; //sizeOfHistogram=0;
    HistogramTemp *node = head;
    while (node != NULL) {
//        sizeOfHistogram += strlen(node->words) + strlen(node->count) + sizeof(HistogramTemp);
        node = node->next;
        numberOfWords++;
    }
    return numberOfWords;
}

void printHistogram (HistogramTemp *head, FILE *fp){
    HistogramTemp *node = head;
    while (node != NULL) {
        fprintf(fp, "%d\t%s\n", node->count, node->words);
        node = node->next;
    }
}

void createNewFile(char *userFilename, HistogramTemp *head) {

    // Create a new file name

    char *token;
    char *fullPath[100];
    char *origianlFileName;

    token = strtok(userFilename, "/\\.");

    int i=0;
    while(token != NULL){
        fullPath[i] = token = strtok(NULL, "/\\.");
        i++;
    }
    origianlFileName = (char*)malloc(sizeof(char)+1);
    strcpy(origianlFileName, fullPath[i-3]);
    char *newFilename = strcat(fullPath[i-3], ".histogram.txt");


    // histogram size + word count
    int numberOfWords=0;
    HistogramTemp *node1 = head;
    while (node1 != NULL) {
        numberOfWords++;
        node1 = node1->next;
    }


    // creating a new text file with histogram info
    FILE *fp;
    fp = fopen(newFilename, "w");
    node1 = head;
    fprintf(fp, "\nInput File: %s.txt\n", origianlFileName );
    fprintf(fp, "Number of Unique words: %d\n\n", countHistogram(node1));
    fprintf(fp, "INDEX\tWORDS\n");

    node1 = head;
    printHistogram(node1, fp);

    fclose(fp);
}

void insertInOrder(HistogramTemp *head, HistogramTemp *node){
    HistogramTemp *previous = NULL;
    HistogramTemp *next = head;

    while (next != NULL && next->count <= node->count) {
        previous = next;
        next = next->next;
    }

    if (previous == NULL) {
        node->next = head;
        *head = *node;
    } else {
        previous->next = node;
        node->next = next;
    }
}
