/**
 * @file packetmanager.h
 * @author Thomas
 * @brief 
 * @version 0.1
 * @date 2020-12-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdbool.h>

#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H


//Structure des messages côté client


/**
 * @brief Structure du paquet ClientInit : Initialisation Client
 */
typedef struct{
int type; /*!< type du paquet : 1 = je suis connecté et je suis le client X. */
int numClient; /*!< numéro du client */
}packetClientInit;


/**
 * @brief Structure du paquet ClientWaitingGame : Client en attente
 */
typedef struct{
int type; /*!< type du paquet : 2 = Je suis en attente d'une partie */
}packetClientWaitingGame;


/**
 * @brief Structure du paquet ClientPlayerReady : Client prêt !
 */
typedef struct{
int type; /*!< type du paquet : 3 = Mon Joueur est prêt / pas prêt */
bool playerIsReady; /*!< true : Joueur prêt, false : Joueur pas prêt */
}packetClientPlayerReady;


/**
 * @brief Structure du paquet ClientPlayerChoice : Choix du Client
 */
typedef struct{
int type; /*!< type du paquet : 4 = Choix du client */
bool choice; /*!< Le choix du joueur est collaborer : false ou trahir : true */
}packetClientPlayerChoice;




//Structure des messages côté serveur


/**
 * @brief Structure du paquet ServerInit : Initialisation Serveur
 */
typedef struct{
int type; /*!< type du paquet : 10 = Message Bonjour Client X, la connexion a été établie */
bool ServerReady; /*!< false si le serveur n'est pas prêt ou true si le serveur est prêt */
}packetServerInit;

/**
 * @brief Structure du paquet ServerWaitingEnd : Fin de l'attente
 */
typedef struct{
int type; /*!< type du paquet : 11 = Message Sortez de votre attente SVP une partie va démarrer ! */
}packetServerWaitingEnd;

/**
 * @brief Structure du paquet ServerIsPlayerReady : Le Joueur est prêt ?
 */
typedef struct{
int type; /*!< type du paquet : 12 = Message Demander a votre joueur si il est prêt */
}packetServerIsPlayerReady;

/**
 * @brief Structure du paquet ServerMakeChoice : Faites un choix !
 */
typedef struct{
int type; /*!< type du paquet : 13 = Message Faites vos jeux */
}packetServerMakeChoice;

/**
 * @brief Structure du paquet ServerIsThisTheEnd : C'est la fin / pas la fin
 */
typedef struct{
int type; /*!< type du paquet : 14 = Message C'est la fin / pas la fin */
bool gameEnd; /*!< gameEnd Continuer = false / Fin de partie = true */
}packetServerIsThisTheEnd;

/**
 * @brief Structure du paquet ServerScore : Envoi score Joueur
 */
typedef struct{
int type; /*!< type du paquet : 15 = Voici votre score */
int score; /*!< score du joueur */
}packetServerScore;





packetClientInit * createPacketClientInit(int clientID);
packetClientWaitingGame * createPacketClientWaitingGame();
packetClientPlayerReady * createPacketClientPlayerReady();
packetClientPlayerChoice * createPacketClientPlayerChoice(bool choice);
void receivePacket(char *buffer_in, int socket);




#endif /* PACKETMANAGER_H */