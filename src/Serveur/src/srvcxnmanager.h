/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   srvcxnmanager.h
 * Author: aurelio
 *
 */

#include <sys/socket.h>

#ifndef SRVCXNMANAGER_H
#define SRVCXNMANAGER_H

#define BUFFERSIZE 2048
#define MAXSIMULTANEOUSCLIENTS 100


typedef struct {
    int sockfd;
    struct sockaddr address;
    int addr_len;
    int index;
} connection_t;

typedef struct{
//int socket;
connection_t *connection;
int ID;
bool choice;
bool waiting;
}player;

extern player* playerPool[100]; //Ensemble des joueurs connectés
extern int newSocket;

/* typedef struct {
    int sockfd;
    struct sockaddr address;
    int addr_len;
    int index;
} connection_t; */

void init_sockets_array();
void add(player *player);
void del(player *player);
void *threadProcess(void *ptr);
int create_server_socket() ;


#endif /* SRVCXNMANAGER_H */

