/**
 * @file fichier_confsrv.c
 * @author Meunier Paul
 * @brief Création du fichier de configuration .ini et lecture des informations
 * @version 0.1
 * @date 2020-12-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ini.h"

#include "fichier_confsrv.h"


static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    configuration* pconfig = (configuration*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

    if (MATCH("Information", "ip")) {
        pconfig->ip = strdup(value);
    } else if (MATCH("Information", "port")) {
        pconfig->port = strdup(value);
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

int config(){
   configuration config;;

    if (ini_parse("Fichier_conf.ini", handler, &config) < 0) {
        printf("Can't load 'Fichier_conf.ini'\n");
        return;
    }
    printf("Config loaded from 'Fichier_conf.ini': ip=%s, port=%s\n", config.ip, config.port);
    return config.ip;
    return config.port;
}