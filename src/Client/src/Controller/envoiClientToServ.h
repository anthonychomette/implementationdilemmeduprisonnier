/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   envoiClientToServ.h
 * Author: student
 *
 * Created on November 18, 2020, 9:17 AM
 */


#ifndef ENVOICLIENTTOSERV_H
#define ENVOICLIENTTOSERV_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif



//Envoi infos de connexion
void clientInitClient(int sockfd, int clientID);
////envoi d'un packetClientInit 

//Envoi le client attend une partie
void ClientWaitingGame(int sockfd);
////envoi d'un packetClientWaitingGame

//Envoi le player est prêt
void clientPlayerReady(int sockfd);
////envoi d'un packet ClientPlayerReady

//Envoi du choix  collaborer
void clientChoiceCollabore(int sockfd);
////Envoi d'un packetClientPlayerChoice packet
////pour collaborer bool choice = 0   (à vérifier dans la structure)
//Envoi du choix trahir
void clientChoiceBetray(int sockfd);
////Envoi d'un packetClientPlayerChoice packet
////pour trahir bool choice = 1       (à vérifier dans la structure)







#endif /* ENVOICLIENTTOSERV_H */

