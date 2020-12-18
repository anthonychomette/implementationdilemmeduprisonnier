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
#include "../packetmanager.h"

#ifndef RECEPTIONSERVTOCLIENT_H
#define RECEPTIONSERVTOCLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif




void serverIsPlayerReady();
void serverWaitingEnd();
void serverMakeChoice(int sockfd);
void serverScore(packetServerScore *packet);
void serverIsThisTheEnd(packetServerIsThisTheEnd packet);
void initView();




#endif /* RECEPTIONSERVTOCLIENT_H */

