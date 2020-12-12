
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "srvcxnmanager.h"
#include <netinet/tcp.h>
#include "packetmanager.h"


#define BEGIN        '{'
#define SEP          ':'
#define BUF_SIZE     128
#define FILENAME     "Fichier_conf.txt"

#define TAG_NAME     "Ip_add"
#define TAG_AGE      "Port"
#define TAG_ADRESS   "Somme"

//connection_t* connections[MAXSIMULTANEOUSCLIENTS];



void init_sockets_array() {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        playerPool[i] = NULL;
    }
}

void add(player *player) {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        if (playerPool[i] == NULL) {
            playerPool[i] = player;
            return;
        }
    }
    perror("Too much simultaneous connections");
    exit(-5);
}

void del(player *player) {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        if (playerPool[i] == player) {
            playerPool[i] = NULL;
            return;
        }
    }
    perror("Connection not in pool ");
    exit(-5);
}
/*
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&lock);
pthread_mutex_unlock(&lock);
 */

/**
 * Thread allowing server to handle multiple client connections
 * @param ptr connection_t 
 * @return 
 */
void *threadProcess(void *ptr) {
    char buffer_in[BUFFERSIZE];
    char buffer_out[BUFFERSIZE];

    int len;
    //connection_t *connection;
    player *Player;

    if (!ptr) pthread_exit(0);
    Player = (player*) ptr;
    printf("New incoming connection \n");

    add(Player);

    //Welcome the new client
    /*printf("Welcome #%i\n", connection->index);
    sprintf(buffer_out, "Welcome #%i\n", connection->index);
    write(connection->sockfd, buffer_out, strlen(buffer_out));

        int *type = buffer_in;
        printf("Le type est : %d ", *type);
        if(*type == 1) 
        {
            paquetClientInit *paquetOK = malloc(1 * sizeof(paquetClientInit));
            memcpy(buffer_in, paquetOK, sizeof(paquetClientInit));
            printf("Le client %d s'est connecté ! ", paquetOK->numClient);
        }*/
    //printf("#######Avant boucle\n");
    while ((len = read(Player->connection->sockfd, buffer_in, BUFFERSIZE)) > 0) {

        //int usedSocket = Player->connection->sockfd;
        receivePacket(buffer_in, Player);
        //printf("Après aiguillage");
        memset(buffer_in, '\0', BUFFERSIZE);
    }
    printf("Connection to client %i ended \n", Player->connection->index);
    close(Player->connection->sockfd);
    del(Player);
    free(Player);
    pthread_exit(0);

}

int create_server_socket() {
    int sockfd = -1;
    struct sockaddr_in address;
    int port = 7799;

    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd <= 0) {
        fprintf(stderr, "%s: error: cannot create socket\n");
        return -3;
    }


    /* bind socket to port */
    address.sin_family = AF_INET;
    //bind to all ip : 
    //address.sin_addr.s_addr = INADDR_ANY;
    //ou 0.0.0.0 
    //Sinon  127.0.0.1
    address.sin_addr.s_addr = inet_addr("0.0.0.0");
    address.sin_port = htons(port);

    /* prevent the 60 secs timeout */
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*) &reuse, sizeof (reuse));

    /* bind */
    if (bind(sockfd, (struct sockaddr *) &address, sizeof (struct sockaddr_in)) < 0) {
        fprintf(stderr, "error: cannot bind socket to port %d\n", port);
        return -4;
    }

    return sockfd;
}

