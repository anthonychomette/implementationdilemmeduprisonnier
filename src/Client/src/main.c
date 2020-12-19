/* 
 * File:   main.c
 * Author: aurelio
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "clientcxnmanager.h"
#include "packetmanager.h"
#include "Controller/envoiClientToServ.h"
#include "confreadwrite.h"
#include <assert.h>
//#include <X11/Xlib.h>

extern GtkBuilder *builder;
configuration* clientInfos;

/**
 * @brief Fonction principale du programme
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char** argv) {

    clientInfos = config();
    int socketfd = open_connection();

    //XInitThreads();
    
    createPthread(socketfd);
    //initView();
    return (EXIT_SUCCESS);
}