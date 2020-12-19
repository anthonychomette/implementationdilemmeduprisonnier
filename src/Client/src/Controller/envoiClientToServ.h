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




void clientInitClient(int sockfd, int clientID);
void ClientWaitingGame(int sockfd);
void clientPlayerReady(int sockfd);
void clientChoiceCollabore(int sockfd);
void clientChoiceBetray(int sockfd);




#endif /* ENVOICLIENTTOSERV_H */