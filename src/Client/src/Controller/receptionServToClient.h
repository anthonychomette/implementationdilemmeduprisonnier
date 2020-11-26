/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   receptionServToClient.h
 * Author: student
 *
 * Created on November 18, 2020, 9:18 AM
 */
#include "packetmanager.h"

#ifndef RECEPTIONSERVTOCLIENT_H
#define RECEPTIONSERVTOCLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

//Reception de la partie a faire êtes vous prets ?
void serverIsPlayerReady();

//Reception attend l'autre joueur
void serverWaitingEnd();

//Reception début partie
void serverMakeChoice();

//Reception résultats
void serverScore(packetServerScore packet);

//Reception fin du round ou continuer
void serverIsThisTheEnd(packetServerIsThisTheEnd packet);

#endif /* RECEPTIONSERVTOCLIENT_H */

