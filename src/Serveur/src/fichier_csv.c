/**
 * @file fichier_csv.c
 * @author Meunier Paul
 * @brief 
 * @version 0.1
 * @date 2020-12-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fichier_csv.h"

void csvFile(){
FILE *fichier;
fichier = fopen("./fichier_csv.csv", "a");
    if(fichier == NULL){
        printf("Ouverture impossible");
        exit(0);
    } 
    fclose(fichier);
}
void csvWriteAndRead(){
    //const char* separators=",";
    char buffer[80];
    //char str=buffer;
    //char *c =malloc(80);
    char *token;

    FILE *fichier;
    fichier = fopen("./fichier_csv.csv", "r");
    for(int i=0; i < 4;i++){
        fgets(&buffer,80,fichier);
        token = strtok(buffer,",/");
        printf("%s ", token);
    }
    /*strcpy(c,str);
    token = strsep(&c, ",");
    printf("%s", token);
    char* token = strtok(str, ",");
    printf("%s", token);
    token = strtok(NULL, ",");
    printf("%s", token);
    return;*/
}

