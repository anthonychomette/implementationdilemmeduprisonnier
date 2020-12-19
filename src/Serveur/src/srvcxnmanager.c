/**
 * @file srvcxnmanager.c
 * @author Thomas
 * @brief 
 * @version 0.1
 * @date 2020-12-17
 * 
 * @copyright Copyright (c) 2020
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
#include "srvcxnmanager.h"
#include <netinet/tcp.h>
#include "packetmanager.h"
#include "fichier_confsrv.h"


#define BEGIN        '{'
#define SEP          ':'
#define BUF_SIZE     128
#define FILENAME     "Fichier_conf.txt"

#define TAG_NAME     "Ip_add"
#define TAG_AGE      "Port"
#define TAG_ADRESS   "Somme"



/**
 * @brief Initalise le tableau de sockets
 * 
 */
void init_sockets_array() {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        playerPool[i] = NULL;
    }
}

/**
 * @brief Ajoute un joueur dans la playerPool
 * 
 * @param Player Joueur à ajouter dans la playerPool
 */
void add(player *Player) {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        if (playerPool[i] == NULL) {
            playerPool[i] = Player;
            return;
        }
    }
    perror("Too much simultaneous connections");
    exit(-5);
}

/**
 * @brief Supprime un joueur dans la playerPool
 * 
 * @param Player Joueur à supprimer
 */
void del(player *Player) {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        if (playerPool[i] == Player) {
            playerPool[i] = NULL;
            return;
        }
    }
    perror("Connection not in pool ");
    exit(-5);
}

/**
 * @brief Ajoute une partie dans la pool
 * 
 * @param Game Partie à ajouter
 */
void addGame(game* Game) {
    for (int i = 0; i < 100; i++) {
        if (gamePool[i] == NULL) {
            gamePool[i] = Game;
            return;
        }
    }
    perror("Too much simultaneous Games");
    exit(-5);
}

/**
 * @brief Supprime une partie de la pool
 * 
 * @param Game Partie à supprimer
 */
void delGame(game* Game) {
    for (int i = 0; i < 100; i++) {
        if (gamePool[i] == Game) {
            gamePool[i] = NULL;
            return;
        }
    }
    perror("Game not in pool ");
    exit(-5);
}

/**
 * @brief Permet de créer une partie et de l'ajouter dans la liste de partie (GamePool)
 * 
 * @param firstClientID ID du premier joueur
 * @param secondClientID ID du second joueur
 * @param numberOfRound nombre de round
 */
void addGameToPool(int firstClientID, int secondClientID, int numberOfRound) {
    game* Game;
    Game = (game *) malloc(sizeof(game));
    Game->firstOpponentID = firstClientID;
    Game->secondOpponentID = secondClientID;
    Game->FirstPlayer = NULL;
    Game->SecondPlayer = NULL;
    Game->roundNumber = numberOfRound*2;
    addGame(Game);
}

/**
 * @brief Fonction permettant d'attendre la connexion de deux joueurs.
 * 
 * @param Game Structure Game contenant les clients à attendre
 */
void waitGame(game* Game) {
   
    while (Game->FirstPlayer == NULL) {
        usleep(1000);
    }

    while (Game->SecondPlayer == NULL) {
        usleep(1000);
    }

    while(Game->FirstPlayer->isReady != true){
        //WaitingPlayer1
        usleep(1000);
    }
    while(Game->SecondPlayer->isReady != true) {
        //WaitingPlayer2
        usleep(1000);
    }
}

/**
 * @brief Cherche la partie pour le joueur donné
 * 
 * @param player joueur pour lequel chercher la partie correspondante 
 */
game * searchGame(player *player) {

    for (int i = 0; i < 100; i++) {
        if (gamePool[i]->firstOpponentID == player->ID) {
            player->lobby = i;
            return gamePool[i];
        }
        else if (gamePool[i]->secondOpponentID == player->ID) {
            player->lobby = i;
            return gamePool[i];
        }
    }
    printf("Pas de partie pour ce joueur %d !!!\n", player->ID);

}

/**
 * @brief Place le joueur prêt
 * 
 * @param Player Joueur à mettre prêt
 */
void setPlayerReady(player * Player) {
    Player->isReady = true;
}

/**
 * @brief Return the opponent for the given player
 * 
 * @param Player Player whose oponent is searched 
 * @return player* Oponent of that player
 */
player * getOpponent(player* Player) {

    game* gameToSearchOponent = searchGame(Player);


    if(Player->ID == gameToSearchOponent->FirstPlayer->ID) {
        //printf ("Le joueur numéro %d a pour adversaire le joueur %d\n", Player->ID, oponentID);
        return gameToSearchOponent->SecondPlayer;
    }
    else if(Player->ID == gameToSearchOponent->SecondPlayer->ID){
        //printf ("Le joueur numéro %d a pour adversaire le joueur %d\n", Player->ID, oponentID);
        return gameToSearchOponent->FirstPlayer;
    }
    else{
        perror("No opponent found");
        exit(-1);
    }
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
    player *Player;

    if (!ptr) pthread_exit(0);
    Player = (player*) ptr;
    printf("New incoming connection \n");

    add(Player);

    //Tant qu'on reçoit des données
    while ((len = read(Player->connection->sockfd, buffer_in, BUFFERSIZE)) > 0) {
        receivePacket(buffer_in, Player);
        memset(buffer_in, '\0', BUFFERSIZE);
    }
    
    printf("Connection to client %i ended \n", Player->ID);
    close(Player->connection->sockfd);
    del(Player);
    free(Player);
    pthread_exit(0);

}

/**
 * @brief Créé un socket de connexion
 * 
 * @return int Return le socket de la connexion créée
 */
int create_server_socket() {
    int sockfd = -1;
    struct sockaddr_in address;
    int port = atoi(serveurInfos->port);
    //int port = 7799;

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
    address.sin_addr.s_addr = inet_addr(serveurInfos->ip);
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