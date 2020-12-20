/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include<string.h>
#include "confreadwrite.h"
#include "ini.h"
#include <stdlib.h>

/**
 * @brief Récupère les données dans le .ini
 * 
 * @param user 
 * @param section 
 * @param name 
 * @param value 
 * @return int return 0 si pas de problèmes
 */
static int handler(void* user,const char* section,const char* name,const char* value)
{
    configuration* pconfig = (configuration*)user;
    #define MATCH(s,n) strcmp(section, s) == 0 && strcmp(name,n) == 0
    
    if (MATCH("database","ip")){
        pconfig->ip= strdup(value);
    } else if (MATCH("database","port")){
        pconfig->port = strdup(value);
    } else if (MATCH("database","IdClient")){
        pconfig->IdClient= strdup(value);
    } else {
        return 0;
    }
    return 1;
 }

 /**
  * @brief Return les données lues dans le .ini
  * 
  * @return configuration* Structure configuration avec la config
  */
configuration * config(){
    configuration* Configuration = malloc(1 * sizeof(configuration));
    
    if (ini_parse("./conf.ini", handler,Configuration) < 0) {
        printf ("Cant't load 'conf.ini'\n");
        printf("Merci de lancer ce client dans le dossier de son exécutable !\n");
        return;
    }

    printf("Config loaded from 'conf.ini' : ip=%s, port=%s\n IdClient=%s\n", Configuration->ip, Configuration->port, Configuration->IdClient);
    return Configuration;
}