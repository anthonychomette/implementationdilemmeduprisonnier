/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   receptionClientToServ.h
 * Author: student
 *
 * Created on November 19, 2020, 8:48 AM
 */

#include "packetmanager.h"

#ifndef RECEPTIONCLIENTTOSERV_H
#define RECEPTIONCLIENTTOSERV_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

//Reception infos de connexion
void servInitClient(packetClientInit packet);

//Reception les clients sont ils prets
void servIsPlayerReady(packetClientPlayerReady packet);

//Reception du choix 
void servChoice(packetClientPlayerChoice packet);
//pour trahir bool choice = 1       (à vérifier dans la structure)
//pour collaborer bool choice = 0   (à vérifier dans la structure)


#endif /* RECEPTIONCLIENTTOSERV_H */

