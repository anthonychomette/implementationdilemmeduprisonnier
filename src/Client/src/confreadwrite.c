/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include<string.h>
#include "confreadwrite.h"
#include "ini.h"
static int handler(void* user,const char* section,const char* name,const char* value)
{
    configuration* pconfig = (configuration*)user;
    #define MATCH(s,n) strcmp(section, s) == 0 && strcmp(name,n) == 0
    
    if (MATCH("database","ip")){
        pconfig->ip= strdup(value);
    } else if (MATCH("database","port")){
        pconfig->port = strdup(value);
    } else if (MATCH("database","numeropc")){
        pconfig->numeropc= strdup(value);
    } else {
        return 0;
    }
    return 1;
 }
void config(){
    configuration config;
    
    if (ini_parse("conf.ini", handler,&config) < 0) {
        printf ("Cant't load 'conf.ini'\n");
        return;
    }
    printf("Config loaded from 'conf.ini' : ip=%s, port=%s\n numeropc=client%p", config.ip, config.port, config.numeropc);
    return;
}