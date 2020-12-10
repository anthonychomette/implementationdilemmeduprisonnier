#include <stdbool.h>

//Structure des messages côté client




#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

/**
 * @brief Structure
 * type est le type du paquet 1 = je suis connecté et je suis le client X
 * numclient est le numéro du client
 */
typedef struct{
int type;
int numClient;
}packetClientInit;


/**
 * @brief Structure
 * type est le type du paquet 2 = Je suis en attente d'une partie
 */
typedef struct{
int type;
}packetClientWaitingGame;


/**
 * @brief Structure
 * type est le type du paquet 3 = Mon Joueur est prêt / pas prêt
 * playerIsReady = Vrai si prêt / Faux si pas prêt
 */
typedef struct{
int type;
bool playerIsReady;
}packetClientPlayerReady;


/**
 * @brief Structure
 * type est le type du paquet 4 = Le choix du joueur est collaborer : 0 ou trahir : 1
 * choice est faux si le joueur collabore et vrai si le joueur trahis
 */
typedef struct{
int type;
bool choice;
}packetClientPlayerChoice;



//Structure des messages côté serveur

/**
 * @brief Structure
 * type est le type du paquet 10 = Message Bonjour Client X, la connexion a été établie
 * ServerReady est faux si le serveur n'est pas prêt ou vrai si le serveur est prêt
 */
typedef struct{
int type; 
bool ServerReady;
}packetServerInit;

/**
 * @brief Structure
 * type est le type du paquet 11 = Message Sortez de votre attente SVP une partie va démarrer !
 */
typedef struct{
int type;
}packetServerWaitingEnd;

/**
 * @brief Structure
 * type est le type du paquet 12 = Message Demander a votre joueur si il est prêt
 */
typedef struct{
int type;
}packetServerIsPlayerReady;

/**
 * @brief Structure
 * type est le type du paquet 13 = Message Faites vos jeux.
 */
typedef struct{
int type;
}packetServerMakeChoice;

/**
 * @brief Structure
 * type est le type du paquet 14 = Message Est-ce la fin ?
 * gameEnd Continuer = 0 / Fin de partie = 1
 */
typedef struct{
int type;
bool gameEnd;
}packetServerIsThisTheEnd;

/**
 * @brief Structure
 * type est le type du paquet 15 = Voici votre score
 * score score du joueur
 */
typedef struct{
int type; 
int score;
}packetServerScore;


/* #define BUFFERSIZE 2048

void *threadProcess(void * ptr);
int open_connection(); */

/**
 * @brief Fonction permettant de créer un paquet ClientInit
 * 
 * @param clientID Numéro d'identification du client
 * @return packetClientInit* 
 */
packetClientInit * createPacketClientInit(int clientID);

/**
 * @brief Fonction permettant de créer un paquet ClientWaitingGame
 * 
 * @return packetClientWaitingGame* 
 */
packetClientWaitingGame * createPacketClientWaitingGame();

/**
 * @brief Fonction permettant de créer un paquet ClientPlayerReady
 * 
 * @return packetClientPlayerReady* 
 */
packetClientPlayerReady * createPacketClientPlayerReady();

/**
 * @brief Fonction permettant de créer un paquet ClientPlayerChoice
 * 
 * @param choice 
 * @return packetClientPlayerChoice* 
 */
packetClientPlayerChoice * createPacketClientPlayerChoice(bool choice);


/**
 * @brief Fonction permettant de créer un paquet ServerInit
 * 
 * @return packetServerInit* 
 */
packetServerInit * createPacketServerInit();

/**
 * @brief Fonction permettant de créer un paquet ServerWaitingEnd
 * 
 * @return packetServerWaitingEnd* 
 */
packetServerWaitingEnd * createPacketServerWaitingEnd();

/**
 * @brief Fonction permettant de créer un paquet ServerIsPlayerReady
 * 
 * @return packetServerIsPlayerReady* 
 */
packetServerIsPlayerReady * createPacketServerIsPlayerReady();

/**
 * @brief Fonction permettant de créer un paquet ServerMakeChoice
 * 
 * @return packetServerMakeChoice* 
 */
packetServerMakeChoice * createPacketServerMakeChoice();

/**
 * @brief Fonction permettant de créer un paquet ServerIsThisTheEnd
 * 
 * @param IsThisTheEnd 
 * @return packetServerIsThisTheEnd* 
 */
packetServerIsThisTheEnd * createPacketServerIsThisTheEnd(bool IsThisTheEnd);

/**
 * @brief Fonction permettant de créer un paquet ServerScore
 * 
 * @param score 
 * @return packetServerScore* 
 */
packetServerScore * createPacketServerScore(int score);

/**
 * @brief Fonction permettant d'aiguiller les paquet reçu vers le bon traitement suivant leurs type
 * 
 * @param buffer_in Paquet brut a determiner
 * @param socket socket pour communiquer avec le client
 */
void receivePacket(char *buffer_in, int socket);

#endif /* PACKETMANAGER_H */