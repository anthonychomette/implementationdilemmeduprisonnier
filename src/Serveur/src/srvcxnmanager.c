
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

connection_t* connections[MAXSIMULTANEOUSCLIENTS];



void init_sockets_array() {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        connections[i] = NULL;
    }
}

void add(connection_t *connection) {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        if (connections[i] == NULL) {
            connections[i] = connection;
            return;
        }
    }
    perror("Too much simultaneous connections");
    exit(-5);
}

void del(connection_t *connection) {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        if (connections[i] == connection) {
            connections[i] = NULL;
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
    connection_t *connection;

    if (!ptr) pthread_exit(0);
    connection = (connection_t *) ptr;
    printf("New incoming connection \n");

    add(connection);

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
    while ((len = read(connection->sockfd, buffer_in, BUFFERSIZE)) > 0) {

        //printf("*****************\n");

//         if (strncmp(buffer_in, "bye", 3) == 0) {
//            break;


//Ancien code bon

      //   int *type = buffer_in;
        //printf("Le type est : %d \n", *type);
        //if(*type == 1) 
        //{
        //    paquetClientInit *paquetOK = malloc(1 * sizeof(paquetClientInit));
        //    //memcpy(buffer_in, paquetOK, sizeof(paquetClientInit));
        //    memcpy(paquetOK, buffer_in, sizeof(paquetClientInit));
        //    int res = paquetOK->numClient;
        //    printf("Le client %d s'est connecté ! \n", res);

        //}

        //printf("Avant aiguillage");
        int usedSocket = connection->sockfd;
        receivePacket(buffer_in, usedSocket);
        //printf("Après aiguillage");
        memset(buffer_in, '\0', BUFFERSIZE);




#if DEBUG
        printf("DEBUG-----------------------------------------------------------\n");
        printf("len : %i\n", len);
        printf("Buffer : %.*s\n", len, buffer_in);
        printf("----------------------------------------------------------------\n");
#endif
        strcpy(buffer_out, "\nServer Echo : ");
        strncat(buffer_out, buffer_in, len);

        if (buffer_in[0] == '@') {
            for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
                if (connections[i] != NULL) {

                    write(connections[i]->sockfd, buffer_out, strlen(buffer_out));
                }
            }
        } else if (buffer_in[0] == '#') {
            int client = 0;
            int read = sscanf(buffer_in, "%*[^0123456789]%d ", &client);
            for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
                if (client == connections[i]->index) {
                    write(connections[i]->sockfd, buffer_out, strlen(buffer_out));
                    break;
                } //no client found ? : we dont care !!
            }
        } else {
            //write(connection->sockfd, buffer_out, strlen(buffer_out));

/*                 printf("Le Serveur envoie un packet\n\n");
                packetServerWaitingEnd *packetSWaitingEnd = createPacketServerWaitingEnd();
                write(connection->sockfd, packetSWaitingEnd, sizeof (packetServerWaitingEnd));
                free(packetSWaitingEnd);  */
        } 

        //clear input buffer */
        memset(buffer_in, '\0', BUFFERSIZE);
    }
    printf("Connection to client %i ended \n", connection->index);
    close(connection->sockfd);
    del(connection);
    free(connection);
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

