/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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

//Envoi de la partie a faire êtes vous prets ?
void serverIsPlayerReady();
////packetServerIsPlayerReady

//Envoi attend l'autre joueur
void serverWaitingEnd(player* Player, packetClientWaitingGame* packetCWaitingGame);
//// envoi d'un packetServerWaitingEnd

//Envoi début partie
void serverMakeChoice(player* Player, packetClientPlayerReady* packetCPlayerReady);
//// envoi d'un packetServerMakeChoice

//Envoi résultats
void serverScore(player* Player, packetClientPlayerChoice* packetCPlayerChoice);
//// envoi d'un packetServerScore

//Envoi fin du round ou continuer
void serverIsThisTheEnd(int sockfd);
//// envoi d'un packetServerIsThisTheEnd

//Envoi  continuer
//void serverIsNotThisTheEnd(int sockfd);
//// envoi d'un packetServerIsThisTheEnd

//envoi server prêt
void serverInit(player* Player, packetClientInit *packetCInit);
//// envoi d'un packetServerInit

#endif /* ENVOISERVTOCLIENT_H */

