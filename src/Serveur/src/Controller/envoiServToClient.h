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

#include "packetmanager.h"

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
void serverWaitingEnd();
//// envoi d'un packetServerWaitingEnd

//Envoi début partie
void serverMakeChoice();
//// envoi d'un packetServerMakeChoice

//Envoi résultats
void serverScore();
//// envoi d'un packetServerScore

//Envoi fin du round ou continuer
void serverIsThisTheEnd();
//// envoi d'un packetServerIsThisTheEnd

#endif /* ENVOISERVTOCLIENT_H */

