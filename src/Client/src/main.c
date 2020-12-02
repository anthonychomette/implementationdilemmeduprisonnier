/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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

#include "clientcxnmanager.h"
#include "packetmanager.h"
#include "Controller/envoiClientToServ.h"
#include "confreadwrite.h"

/*
 * 
 */
int main(int argc, char** argv) {

    //recuperation du clientID depuis le fichier de conf
    int clientID = 4;
    //int socketfd = createSocket();
    int socketfd = open_connection();
    config();

    //Envoi d'un paquet d'Init
    clientInitClient(socketfd, clientID);

    usleep(10000); //Pause de 10 ms ne pas utiliser

    //Envoi d'un paquet d'Attente
    ClientWaitingGame(socketfd);

    createPthread(socketfd);
    return (EXIT_SUCCESS);
}

