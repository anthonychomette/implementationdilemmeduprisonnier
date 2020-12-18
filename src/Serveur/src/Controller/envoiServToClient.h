/* 
 * File:   envoiServToClient.h
 * Author: student
 *
 * Created on November 19, 2020, 8:46 AM
 */

#include "../packetmanager.h"



#ifndef ENVOISERVTOCLIENT_H
#define ENVOISERVTOCLIENT_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif




void serverIsPlayerReady();
void serverWaitingEnd(player* Player, packetClientWaitingGame* packetCWaitingGame);
void serverMakeChoice(player* Player, packetClientPlayerReady* packetCPlayerReady);
void serverScore(player* Player, packetClientPlayerChoice* packetCPlayerChoice);
void serverIsThisTheEnd(int sockfd);
void serverInit(player* Player, packetClientInit *packetCInit);
void serverItIsNotTheEnd(int sockfd);




#endif /* ENVOISERVTOCLIENT_H */

