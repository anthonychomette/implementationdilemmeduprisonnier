//Structure des messages côté client
typedef struct{
int type; //Type 1 Message je suis connecté et je suis le client X
int numClient;
bool clientReady;
}packetClientInit;

typedef struct{
int type; //Type 2 Je suis en attente d'une partie
}packetClientWaitingGame;

typedef struct{
int type; //Type 3 Mon Joueur est prêt / pas prêt
bool playerIsReady;
}packetClientPlayerReady;

typedef struct{
int type; //Type 4 Le choix du joueur est collaborer : 0 ou trahir : 1
bool choice;
}packetClientPlayerChoice;



//Structures des messages côté serveur
typedef struct{
int type; //Type 10 Message Bonjour Client X, la connexion a été établie
bool ServerReady;
}packetServerInit;

typedef struct{
int type; //Type 11 Message Sortez de votre attente SVP une partie va démarrer !
}packetServerWaitingEnd;

typedef struct{
int type; //Type 12 Message Demander a votre joueur si il est prêt
}packetServerIsPlayerReady;

typedef struct{
int type; //Type 13 Message Faites vos jeux.
}packetServerMakeChoice;

typedef struct{
int type; //Type 14 Message Est-ce la fin ?.
bool gameEnd; // Continuer = 0 / Fin de partie = 1
}packetServerIsThisTheEnd;

typedef struct{
int type; //Type 15 Voici votre score
int score;
}packetServerScore;


#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

/* #define BUFFERSIZE 2048

void *threadProcess(void * ptr);
int open_connection(); */


packetClientInit * createPacketClientInit(int clientID);
packetClientWaitingGame * createPacketClientWaitingGame();
packetClientPlayerReady * createPacketClientPlayerReady();
packetClientPlayerChoice * createPacketClientPlayerChoice(bool choice);



packetServerInit * createPacketServerInit();
packetServerWaitingEnd * createPacketServerWaitingEnd();
packetServerIsPlayerReady * createPacketServerIsPlayerReady();
packetServerMakeChoice * createPacketServerMakeChoice();
packetServerIsThisTheEnd * createPacketServerIsThisTheEnd(bool IsThisTheEnd);
packetServerScore * createPacketServerScore(int score);



void sendPacket(int sockfd, int packetType, int option) ;
void receivePacket(char *buffer_in);

#endif /* PACKETMANAGER_H */