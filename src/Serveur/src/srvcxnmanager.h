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

/**
 * @brief Structure connection_t contenant les paramètres de connexion
 * 
 */
typedef struct {
    int sockfd; /*!< Socket de la connexion */
    struct sockaddr address; /*!< Adresse IP */
    int addr_len; /*!< Taille Adresse */
    int index; /*!< Index */
} connection_t;

/**
 * @brief Structure player contenant les informations du joueur
 * 
 */
typedef struct{
connection_t *connection; /*!< paramètres de connexion du joueur */
int ID; /*!< Identifiant du joueur */
bool choice; /*!< Choix du joueur */
bool isReady; /*!< True : Le joueur est en prêt, False : Il n'est pas prêt*/
int lobby; /*!< lobby du joueur */
}player;

/**
 * @brief Structure game contenant les informations de la partie
 * 
 */
typedef struct{
int roundNumber; /*!< Nombre de round pour la partie (x2 pour le bon fonctionnement du programme)*/
player* FirstPlayer;
player* SecondPlayer;
int firstOpponentID;
int secondOpponentID;
}game;

extern player* playerPool[MAXSIMULTANEOUSCLIENTS]; //Ensemble des joueurs connectés
extern game* gamePool[MAXSIMULTANEOUSCLIENTS]; //Ensemble des parties à jouées

void init_sockets_array();
void add(player *player);
void del(player *player);
void *threadProcess(void *ptr);
int create_server_socket() ;
void addGameToPool(int firstClientID, int secondClientID, int numberOfRound);
void delGame(game* Game);
void addGame(game* Game);
void waitGame(game* Game);
game * searchGame(player *player);
player * getOpponent(player *Player);
void setPlayerReady(player * Player);




#endif /* SRVCXNMANAGER_H */

